#include "PageCache.h"

// 静态成员变量，类内声明，类外定义
PageCache PageCache::_pageCacheInstance;


SpanNode* PageCache::GetKPage(size_t k) {
	assert(k > 0);

	if (k >= MAX_PAGE) {
		void* newMemory = Utils::SystemAllocate(k);
		SpanNode* bigSpan = _spanNodePool.New();
		bigSpan->_pageNum = k;
		bigSpan->_pageID = (PAGE_ID)newMemory >> PAGE_SHIFT;
		bigSpan->_size = k << PAGE_SHIFT;
		_pageIDToSpan[bigSpan->_pageID] = bigSpan;
		return bigSpan;
	}

	// 当前页缓存第k个不为空
	if (!_pageCache[k].Empty()) {
		SpanNode* splitSpan = _pageCache[k].PopFront();
		for (int i = 0; i < splitSpan->_pageNum; i++) {
			_pageIDToSpan[splitSpan->_pageID + i] = splitSpan;
		}
		return splitSpan;
	}

	// 从第k个位置往下找到不为的空位置
	for (size_t i = k; i < MAX_PAGE; i++) {
		if (!_pageCache[i].Empty()) {
			// 分割
			SpanNode* RemainSpan = _pageCache[i].PopFront();
			SpanNode* splitSpan = _spanNodePool.New();
			// 切分后页数更新
			splitSpan->_pageNum = k;
			RemainSpan->_pageNum -= k;
			// 切分后页号更新（页号是找到所申请内存的地址映射）
			splitSpan->_pageID = RemainSpan->_pageID;
			RemainSpan->_pageID += k;
			_pageCache[RemainSpan->_pageNum].PushFront(RemainSpan);

			// 映射管理
			// bigSpan只由PageCache管理，所以只需要将该Span页区间首位映射到该Span，方便pageCache合并连续Span
			_pageIDToSpan[RemainSpan->_pageID] = RemainSpan;
			_pageIDToSpan[RemainSpan->_pageID + RemainSpan->_pageNum - 1] = RemainSpan;
			// 取出的所有页都要进行映射，释放时才能找到对应Span
			for (int i = 0; i < splitSpan->_pageNum; i++) {
				_pageIDToSpan[splitSpan->_pageID + i] = splitSpan;
			}
			// 挂到CentralCache表示当前Span被使用
			splitSpan->_isUse = true;
			return splitSpan;
		}
	}
	// 从堆空间申请新的内存
	void* newMemory = Utils::SystemAllocate(MAX_PAGE - 1);
	SpanNode* newSpan = _spanNodePool.New();
	newSpan->_pageNum = MAX_PAGE - 1;
	newSpan->_pageID = (PAGE_ID)newMemory >> PAGE_SHIFT;
	_pageCache[MAX_PAGE - 1].PushFront(newSpan);
	return GetKPage(k);
}

void PageCache::ReturnFromCentralCache(SpanNode* returnSpan) {
	assert(returnSpan);
	if (returnSpan->_pageNum >= MAX_PAGE) {
		void* freeAddress = (void*)(returnSpan->_pageID << PAGE_SHIFT);
		Utils::SystemDeallocate(freeAddress);
		return;
	}

	// 合并检查
	// 归还Span的前一个Span是否在PageCache中
	while (1) {
		auto prev = _pageIDToSpan.find(returnSpan->_pageID - 1);
		// 没找到，结束合并
		if (prev == _pageIDToSpan.end()) {
			break;
		}
		SpanNode* prevSpan = prev->second;
		// 如果该span在使用，结束合并
		if (prevSpan->_isUse == true) {
			break;
		}
		// 如果超出Page限制，结束合并
		if (prevSpan->_pageNum + returnSpan->_pageNum > MAX_PAGE) {
			break;
		}
		_pageCache[prevSpan->_pageNum].Erase(prevSpan);
		returnSpan->_pageID = prevSpan->_pageID;
		returnSpan->_pageNum += prevSpan->_pageNum;
		_spanNodePool.Delete(prevSpan);
	}
	while (1) {
		auto next = _pageIDToSpan.find(returnSpan->_pageID - returnSpan->_pageNum);
		// 没找到，结束合并
		if (next == _pageIDToSpan.end()) {
			break;
		}
		SpanNode* nextSpan = next->second;
		// 如果该span在使用，结束合并
		if (nextSpan->_isUse == true) {
			break;
		}
		// 如果超出Page限制，结束合并
		if (nextSpan->_pageNum + returnSpan->_pageNum > MAX_PAGE) {
			break;
		}
		_pageCache[nextSpan->_pageNum].Erase(nextSpan);
		returnSpan->_pageNum += nextSpan->_pageNum;
		_spanNodePool.Delete(nextSpan);
	}

	_pageCache[returnSpan->_pageNum].PushFront(returnSpan);
	_pageIDToSpan[returnSpan->_pageID] = returnSpan;
	_pageIDToSpan[returnSpan->_pageID + returnSpan->_pageNum - 1] = returnSpan;
	
} 

// 地址映射Span
SpanNode* PageCache::MapAddressToSpan(void* address) {
	assert(address);
	std::unique_lock<std::mutex> lock(_pageMutex);
	size_t pageID = (PAGE_ID)address >> PAGE_SHIFT;
	auto map = _pageIDToSpan.find(pageID);
	if (map != _pageIDToSpan.end()) {
		return map->second;
	}
	else {
		assert(false);
		return nullptr;
	}
}
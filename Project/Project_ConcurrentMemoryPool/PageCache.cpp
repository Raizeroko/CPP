#include "PageCache.h"

// 静态成员变量，类内声明，类外定义
PageCache PageCache::_pageCacheInstance;


SpanNode* PageCache::GetKPage(size_t k) {
	assert(k > 0 && k < MAX_PAGE);

	// 当前页缓存第k个不为空
	if (!_pageCache[k].Empty()) {
		return _pageCache[k].PopFront();
	}

	// 从第k个位置往下找到不为的空位置
	for (int i = k; i < MAX_PAGE; i++) {
		if (!_pageCache[i].Empty()) {
			// 分割
			SpanNode* bigSpan = _pageCache[i].PopFront();
			SpanNode* splitSpan = new SpanNode;
			// 切分后页数更新
			splitSpan->_pageNum = k;
			bigSpan->_pageNum -= k;
			// 切分后页号更新（页号是找到所申请内存的地址映射）
			splitSpan->_pageID = bigSpan->_pageID;
			bigSpan->_pageID += k;
			_pageCache[bigSpan->_pageNum].PushFront(bigSpan);

			// 映射管理
			// bigSpan只由PageCache管理，所以只需要将该Span页区间首位映射到该Span，方便pageCache合并连续Span
			_pageIDToSpan[bigSpan->_pageID] = bigSpan;
			_pageIDToSpan[bigSpan->_pageID + bigSpan->_pageNum - 1] = bigSpan;
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
	SpanNode* newSpan = new SpanNode;
	newSpan->_pageNum = MAX_PAGE - 1;
	newSpan->_pageID = (PAGE_ID)newMemory >> PAGE_SHIFT;
	_pageCache[MAX_PAGE - 1].PushFront(newSpan);
	return GetKPage(k);
}

void PageCache::ReturnFromCentralCache(SpanNode* returnSpan) {
	assert(returnSpan);


	// 合并检查
	// 归还Span的前一个Span是否在PageCache中
	while (1) {
		auto prev = _pageIDToSpan.find(returnSpan->_pageID - 1);
		// 没找到，结束合并
		if (prev == _pageIDToSpan.end()) {
			break;
		}
		// 如果该span在使用，结束合并
		
		// 如果超出Page限制，结束合并
		SpanNode* prevSpan = prev->second;
		if (prevSpan->_pageNum + returnSpan->_pageNum > MAX_PAGE) {
			break;
		}
		_pageCache[prevSpan->_pageNum].Erase(prevSpan);
		returnSpan->_pageID = prevSpan->_pageID;
		returnSpan->_pageNum += prevSpan->_pageNum;
		delete prevSpan;
	}
	while (1) {
		auto next = _pageIDToSpan.find(returnSpan->_pageID - returnSpan->_pageNum);
		// 没找到，结束合并
		if (next == _pageIDToSpan.end()) {
			break;
		}
		// 如果该span在使用，结束合并

		// 如果超出Page限制，结束合并
		SpanNode* nextSpan = next->second;
		if (nextSpan->_pageNum + returnSpan->_pageNum > MAX_PAGE) {
			break;
		}
		_pageCache[nextSpan->_pageNum].Erase(nextSpan);
		returnSpan->_pageNum += nextSpan->_pageNum;
		delete nextSpan;
	}

	_pageCache[returnSpan->_pageNum].PushFront(returnSpan);
	_pageIDToSpan[returnSpan->_pageID] = returnSpan;
	_pageIDToSpan[returnSpan->_pageID + returnSpan->_pageNum - 1] = returnSpan;
	
} 

// 地址映射Span
SpanNode* PageCache::MapAddressToSpan(void* address) {
	size_t pageID = (PAGE_ID)address >> PAGE_SHIFT;
	return _pageIDToSpan[pageID];
}
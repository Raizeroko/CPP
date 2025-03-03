#include "PageCache.h"

// ��̬��Ա�������������������ⶨ��
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

	// ��ǰҳ�����k����Ϊ��
	if (!_pageCache[k].Empty()) {
		SpanNode* splitSpan = _pageCache[k].PopFront();
		for (int i = 0; i < splitSpan->_pageNum; i++) {
			_pageIDToSpan[splitSpan->_pageID + i] = splitSpan;
		}
		return splitSpan;
	}

	// �ӵ�k��λ�������ҵ���Ϊ�Ŀ�λ��
	for (size_t i = k; i < MAX_PAGE; i++) {
		if (!_pageCache[i].Empty()) {
			// �ָ�
			SpanNode* RemainSpan = _pageCache[i].PopFront();
			SpanNode* splitSpan = _spanNodePool.New();
			// �зֺ�ҳ������
			splitSpan->_pageNum = k;
			RemainSpan->_pageNum -= k;
			// �зֺ�ҳ�Ÿ��£�ҳ�����ҵ��������ڴ�ĵ�ַӳ�䣩
			splitSpan->_pageID = RemainSpan->_pageID;
			RemainSpan->_pageID += k;
			_pageCache[RemainSpan->_pageNum].PushFront(RemainSpan);

			// ӳ�����
			// bigSpanֻ��PageCache��������ֻ��Ҫ����Spanҳ������λӳ�䵽��Span������pageCache�ϲ�����Span
			_pageIDToSpan[RemainSpan->_pageID] = RemainSpan;
			_pageIDToSpan[RemainSpan->_pageID + RemainSpan->_pageNum - 1] = RemainSpan;
			// ȡ��������ҳ��Ҫ����ӳ�䣬�ͷ�ʱ�����ҵ���ӦSpan
			for (int i = 0; i < splitSpan->_pageNum; i++) {
				_pageIDToSpan[splitSpan->_pageID + i] = splitSpan;
			}
			// �ҵ�CentralCache��ʾ��ǰSpan��ʹ��
			splitSpan->_isUse = true;
			return splitSpan;
		}
	}
	// �Ӷѿռ������µ��ڴ�
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

	// �ϲ����
	// �黹Span��ǰһ��Span�Ƿ���PageCache��
	while (1) {
		auto prev = _pageIDToSpan.find(returnSpan->_pageID - 1);
		// û�ҵ��������ϲ�
		if (prev == _pageIDToSpan.end()) {
			break;
		}
		SpanNode* prevSpan = prev->second;
		// �����span��ʹ�ã������ϲ�
		if (prevSpan->_isUse == true) {
			break;
		}
		// �������Page���ƣ������ϲ�
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
		// û�ҵ��������ϲ�
		if (next == _pageIDToSpan.end()) {
			break;
		}
		SpanNode* nextSpan = next->second;
		// �����span��ʹ�ã������ϲ�
		if (nextSpan->_isUse == true) {
			break;
		}
		// �������Page���ƣ������ϲ�
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

// ��ַӳ��Span
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
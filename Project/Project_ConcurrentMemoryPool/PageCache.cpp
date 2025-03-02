#include "PageCache.h"

// ��̬��Ա�������������������ⶨ��
PageCache PageCache::_pageCacheInstance;


SpanNode* PageCache::GetKPage(size_t k) {
	assert(k > 0 && k < MAX_PAGE);

	// ��ǰҳ�����k����Ϊ��
	if (!_pageCache[k].Empty()) {
		return _pageCache[k].PopFront();
	}

	// �ӵ�k��λ�������ҵ���Ϊ�Ŀ�λ��
	for (int i = k; i < MAX_PAGE; i++) {
		if (!_pageCache[i].Empty()) {
			// �ָ�
			SpanNode* bigSpan = _pageCache[i].PopFront();
			SpanNode* splitSpan = new SpanNode;
			// �зֺ�ҳ������
			splitSpan->_pageNum = k;
			bigSpan->_pageNum -= k;
			// �зֺ�ҳ�Ÿ��£�ҳ�����ҵ��������ڴ�ĵ�ַӳ�䣩
			splitSpan->_pageID = bigSpan->_pageID;
			bigSpan->_pageID += k;
			_pageCache[bigSpan->_pageNum].PushFront(bigSpan);

			// ӳ�����
			// bigSpanֻ��PageCache��������ֻ��Ҫ����Spanҳ������λӳ�䵽��Span������pageCache�ϲ�����Span
			_pageIDToSpan[bigSpan->_pageID] = bigSpan;
			_pageIDToSpan[bigSpan->_pageID + bigSpan->_pageNum - 1] = bigSpan;
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
	SpanNode* newSpan = new SpanNode;
	newSpan->_pageNum = MAX_PAGE - 1;
	newSpan->_pageID = (PAGE_ID)newMemory >> PAGE_SHIFT;
	_pageCache[MAX_PAGE - 1].PushFront(newSpan);
	return GetKPage(k);
}

void PageCache::ReturnFromCentralCache(SpanNode* returnSpan) {
	assert(returnSpan);


	// �ϲ����
	// �黹Span��ǰһ��Span�Ƿ���PageCache��
	while (1) {
		auto prev = _pageIDToSpan.find(returnSpan->_pageID - 1);
		// û�ҵ��������ϲ�
		if (prev == _pageIDToSpan.end()) {
			break;
		}
		// �����span��ʹ�ã������ϲ�
		
		// �������Page���ƣ������ϲ�
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
		// û�ҵ��������ϲ�
		if (next == _pageIDToSpan.end()) {
			break;
		}
		// �����span��ʹ�ã������ϲ�

		// �������Page���ƣ������ϲ�
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

// ��ַӳ��Span
SpanNode* PageCache::MapAddressToSpan(void* address) {
	size_t pageID = (PAGE_ID)address >> PAGE_SHIFT;
	return _pageIDToSpan[pageID];
}
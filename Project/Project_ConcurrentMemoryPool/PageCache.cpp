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

void PageCache::ReturnToPageCache(SpanNode* span) {
	;
}
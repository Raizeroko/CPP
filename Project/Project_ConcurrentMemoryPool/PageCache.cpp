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

void PageCache::ReturnToPageCache(SpanNode* span) {
	;
}
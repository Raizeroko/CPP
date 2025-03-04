#pragma once

#include "Span.h"
#include "Utils.h"
#include "FixedLengthMemoryPool.h"
#include <unordered_map>

class PageCache {
public:
	SpanNode* GetKPage(size_t k);
	void ReturnFromCentralCache(SpanNode* span);
	SpanNode* MapAddressToSpan(void* address);

private:
	// ��Ա����
	SpanList _pageCache[MAX_PAGE];
	std::unordered_map<PAGE_ID, SpanNode*> _pageIDToSpan;
public:
	FixedLengthMemoryPool<SpanNode> _spanNodePool;
	std::mutex _pageMutex;


// ����ģʽ
public:
	// ��ȡʵ��
	static PageCache* GetInstance() {
		return &_pageCacheInstance;
	}
private:
	// ����ʵ��
	static PageCache _pageCacheInstance;
private:
	PageCache(){}
	// ��ֹ��������
	PageCache(const PageCache& copy) = delete;
	void operator=(const PageCache& copy) = delete;
};
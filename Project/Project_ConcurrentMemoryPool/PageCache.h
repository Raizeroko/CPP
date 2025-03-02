#pragma once

#include "Span.h"
#include "Utils.h"
#include <unordered_map>

class PageCache {
public:
	SpanNode* GetKPage(size_t k);
	void ReturnFromCentralCache(SpanNode* span);
	SpanNode* MapAddressToSpan(void* address);

private:
	// ��Ա����
	SpanList _pageCache[MAX_PAGE];
	std::unordered_map<size_t, SpanNode*> _pageIDToSpan;
public:
	std::mutex _centralMutex;


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
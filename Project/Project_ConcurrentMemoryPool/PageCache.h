#pragma once

#include "Span.h"
#include "Utils.h"


class PageCache {
public:
	SpanNode* GetKPage(size_t k);
	void ReturnToPageCache(SpanNode* span);

private:
	// ��Ա����
	SpanList _pageCache[MAX_PAGE];
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
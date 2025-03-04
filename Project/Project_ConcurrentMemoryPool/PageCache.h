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
	// 成员变量
	SpanList _pageCache[MAX_PAGE];
	std::unordered_map<PAGE_ID, SpanNode*> _pageIDToSpan;
public:
	FixedLengthMemoryPool<SpanNode> _spanNodePool;
	std::mutex _pageMutex;


// 单例模式
public:
	// 获取实例
	static PageCache* GetInstance() {
		return &_pageCacheInstance;
	}
private:
	// 生成实例
	static PageCache _pageCacheInstance;
private:
	PageCache(){}
	// 禁止拷贝构造
	PageCache(const PageCache& copy) = delete;
	void operator=(const PageCache& copy) = delete;
};
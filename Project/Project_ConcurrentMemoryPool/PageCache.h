#pragma once

#include "Span.h"
#include "Utils.h"


class PageCache {
public:
	SpanNode* GetKPage(size_t k);
	void ReturnToPageCache(SpanNode* span);

private:
	// 成员变量
	SpanList _pageCache[MAX_PAGE];
public:
	std::mutex _centralMutex;


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
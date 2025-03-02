#pragma once
#include "Span.h"
#include "Utils.h"

class CentralCache {
public:
	SpanNode* GetOneSpan(SpanList& spanList, size_t alignSize);
	size_t FetchToThreadCache(void*& start, void*& end, size_t batchSize, size_t alignSize);
	void ReturnFromThreadCache(void* start, size_t alignSize);

private:
	// CentralCache结构，n个SpanList的哈希结构
	SpanList _centralCache[HARSH_SIZE];

	// 将CentralCache设计为单例模式（懒汉式）
public:
	// 单例模式获取实例
	static CentralCache* GetInstance() {
		return &_centralCacheInstance;
	}

private:
	CentralCache(){}
	// 单例模式禁止拷贝构造
	CentralCache(const CentralCache& copy) = delete;
	void operator=(const CentralCache& copy) = delete;

	// 单例模式实例
	static CentralCache _centralCacheInstance;
};



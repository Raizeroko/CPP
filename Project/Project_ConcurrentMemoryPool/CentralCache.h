#pragma once
#include "Span.h"
#include "Utils.h"

class CentralCache {
public:
	// 获取一个非空的span
	SpanNode* GetOneSpan(SpanList& list, size_t size)
	{
		return nullptr;
	}

	// 从中心缓存获取一定数量的对象给thread cache
	size_t FetchToThreadCache(void*& start, void*& end, size_t batchSize, size_t alignSize)
	{
		size_t index = Utils::Index(alignSize);

		// 不同线程可能同时对中心线程同一个SpanList访问，所以需要加锁
		_centralCache[index]._mutex.lock();

		// 传alignSize??
		SpanNode* spanHead = GetOneSpan(_centralCache[index], alignSize);
		assert(spanHead);
		assert(spanHead->_freeList);
		start = spanHead->_freeList;
		end = start;
		size_t actualSize = 0;
		while (FreeList::Next(end) != nullptr && actualSize < batchSize) {
			actualSize++;
			end = FreeList::Next(end);
		}
		spanHead->_freeList = FreeList::Next(end);
		FreeList::Next(end) = nullptr;

		_centralCache[index]._mutex.unlock();

		return actualSize;
	}
	
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
	// 单例模式禁止拷贝和构造
	CentralCache() = delete;
	CentralCache(CentralCache& copy) = delete;

	// 单例模式实例
	static CentralCache _centralCacheInstance;
};
#pragma once
#include "FreeList.h"
#include "HarshMapRules.h"
#include <thread>


class ThreadCache {
public:
	void* getMemoryFromCentralCache(size_t memorySize) {
		return nullptr;
	}

	// 申请和释放内存对象
	void* Allocate(size_t allocateMemorySize) {
		size_t index = HarshMap().Index(allocateMemorySize);
		size_t memorySize = HarshMap().AlignSize(allocateMemorySize);
		if (!_threadCache[index].Empty()) {
			return _threadCache->Pop();
		}
		return getMemoryFromCentralCache(memorySize);
	}
	void Deallocate(void* ptr, size_t allocateMemorySize) {
		size_t index = HarshMap().Index(allocateMemorySize);
		_threadCache[index].Push(ptr);
	}




	FreeList _threadCache[HARSH_SIZE];
};

// 线程本地存储
thread_local ThreadCache* LocalThreadCache = nullptr;
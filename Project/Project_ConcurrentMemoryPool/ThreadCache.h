#pragma once
#include "FreeList.h"
#include "Utils.h"
#include <thread>
#include <algorithm>
#include "CentralCache.h"


class ThreadCache {
public:
	void* FetchFromCentralCache(size_t index, size_t alignSize) {
		// 慢启动，随着需求的增大而增大，但是最大也不能超过移动批量的上限
		size_t upper = Utils::MoveBatchUpperLimit(alignSize);
		size_t batchSize = std::min(_threadCache[index].FetchBatch(), upper);
		if (batchSize == _threadCache[index].FetchBatch()) {
			_threadCache[index].FetchBatch() += 1;
		}

		// 从中心缓存取出批量的内存
		// 批量链接结点的头尾
		void* start = nullptr;
		void* end = nullptr;
		// 中心缓存不足以分配足量的内存，返回真实的数量。
		size_t actualSize = CentralCache::GetInstance()->FetchToThreadCache(start, end, batchSize, alignSize);
		assert(actualSize != 0);

		if (actualSize == 1) {
			// 为1就直接就把内存返回，不用挂入ThreadCache
			assert(start == end);
		}
		else {
			// 不为1就把头结点返回，剩下的挂入ThreadCache
			_threadCache[index].Push(FreeList::Next(start), end);
		}

		return start;
	}

	// 申请和释放内存对象
	void* Allocate(size_t allocateMemorySize) {
		size_t index = Utils::Index(allocateMemorySize);
		size_t alignSize = Utils::AlignSize(allocateMemorySize);
		if (!_threadCache[index].Empty()) {
			return _threadCache->Pop();
		}
		return FetchFromCentralCache(index, alignSize);
	}
	void Deallocate(void* ptr, size_t allocateMemorySize) {
		size_t index = Utils::Index(allocateMemorySize);
		_threadCache[index].Push(ptr);
	}

	FreeList _threadCache[HARSH_SIZE];
};

// 线程本地存储
thread_local ThreadCache* LocalThreadCache = nullptr;
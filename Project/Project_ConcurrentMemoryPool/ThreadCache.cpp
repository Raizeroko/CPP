#include "ThreadCache.h"

#include "CentralCache.h"

// thread_local ThreadCache* LocalThreadCache;

void* ThreadCache::FetchFromCentralCache(size_t index, size_t alignSize) {
	assert(index >= 0 && index < HARSH_SIZE);
	assert(alignSize > 0 && alignSize < MAX_SIZE);
	// 慢启动，随着需求的增大而增大，但是最大也不能超过移动批量的上限
	size_t upper = Utils::MoveBatchUpperLimit(alignSize);
	size_t batchSize = min(_threadCache[index].BatchSize(), upper);
	if (batchSize == _threadCache[index].BatchSize()) {
		_threadCache[index].BatchSize() += 1;
	}

	// 从中心缓存取出批量的内存
	// 批量链接结点的头尾
	void* start = nullptr;
	void* end = nullptr;
	// 中心缓存不足以分配足量的内存，返回真实的数量。
	size_t actualSize = CentralCache::GetInstance()->FetchToThreadCache(start, end, batchSize, alignSize);
	assert(actualSize != 0);

	size_t i = 0;
	void* cur = start;
	while (cur) {
		cur = FreeList::Next(cur);
		i++;
	}
	if (i != actualSize) {
		int x = 0;
	}

	if (actualSize == 1) {
		// 为1就直接就把内存返回，不用挂入ThreadCache
		assert(start == end);
	}
	else {
		// 不为1就把头结点返回，剩下的挂入ThreadCache
		_threadCache[index].Push(FreeList::Next(start), end, actualSize - 1);
	}

	return start;
}

void* ThreadCache::Allocate(size_t allocateMemorySize) {
	assert(allocateMemorySize > 0 && allocateMemorySize < MAX_SIZE);
	size_t index = Utils::Index(allocateMemorySize);
	size_t alignSize = Utils::AlignSize(allocateMemorySize);
	if (!_threadCache[index].Empty()) {
		return _threadCache[index].Pop();
	}
	return FetchFromCentralCache(index, alignSize);
}


void ThreadCache::Deallocate(void* ptr, size_t deallocateMemorySize) {
	assert(deallocateMemorySize > 0 && deallocateMemorySize < MAX_SIZE);

	size_t index = Utils::Index(deallocateMemorySize);
	size_t alignSize = Utils::AlignSize(deallocateMemorySize);
	_threadCache[index].Push(ptr);
	// 当前往centralCache归还
	if (_threadCache[index].Size() >= _threadCache[index].BatchSize()) {
		ReturnToCentralCache(_threadCache[index], alignSize);
	}

}


void ThreadCache::ReturnToCentralCache(FreeList& returnList, size_t alignSize) {
	assert(alignSize > 0 && alignSize < MAX_SIZE);

	// Pop出BatchSize个结点归还给CentralCache
	void* start = returnList.Pop(returnList.BatchSize());

	CentralCache::GetInstance()->ReturnFromThreadCache(start, alignSize);
}
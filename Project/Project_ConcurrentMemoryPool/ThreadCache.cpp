#include "ThreadCache.h"

#include "CentralCache.h"

// thread_local ThreadCache* LocalThreadCache;

void* ThreadCache::FetchFromCentralCache(size_t index, size_t alignSize) {
	assert(index >= 0 && index < HARSH_SIZE);
	assert(alignSize > 0 && alignSize < MAX_SIZE);
	// �������������������������󣬵������Ҳ���ܳ����ƶ�����������
	size_t upper = Utils::MoveBatchUpperLimit(alignSize);
	size_t batchSize = min(_threadCache[index].BatchSize(), upper);
	if (batchSize == _threadCache[index].BatchSize()) {
		_threadCache[index].BatchSize() += 1;
	}

	// �����Ļ���ȡ���������ڴ�
	// �������ӽ���ͷβ
	void* start = nullptr;
	void* end = nullptr;
	// ���Ļ��治���Է����������ڴ棬������ʵ��������
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
		// Ϊ1��ֱ�ӾͰ��ڴ淵�أ����ù���ThreadCache
		assert(start == end);
	}
	else {
		// ��Ϊ1�Ͱ�ͷ��㷵�أ�ʣ�µĹ���ThreadCache
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
	// ��ǰ��centralCache�黹
	if (_threadCache[index].Size() >= _threadCache[index].BatchSize()) {
		ReturnToCentralCache(_threadCache[index], alignSize);
	}

}


void ThreadCache::ReturnToCentralCache(FreeList& returnList, size_t alignSize) {
	assert(alignSize > 0 && alignSize < MAX_SIZE);

	// Pop��BatchSize�����黹��CentralCache
	void* start = returnList.Pop(returnList.BatchSize());

	CentralCache::GetInstance()->ReturnFromThreadCache(start, alignSize);
}
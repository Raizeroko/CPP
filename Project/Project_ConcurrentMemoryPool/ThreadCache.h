#pragma once
#include "FreeList.h"
#include "Utils.h"
#include <thread>
#include <algorithm>
#include "CentralCache.h"


class ThreadCache {
public:
	void* FetchFromCentralCache(size_t index, size_t alignSize) {
		// �������������������������󣬵������Ҳ���ܳ����ƶ�����������
		size_t upper = Utils::MoveBatchUpperLimit(alignSize);
		size_t batchSize = std::min(_threadCache[index].FetchBatch(), upper);
		if (batchSize == _threadCache[index].FetchBatch()) {
			_threadCache[index].FetchBatch() += 1;
		}

		// �����Ļ���ȡ���������ڴ�
		// �������ӽ���ͷβ
		void* start = nullptr;
		void* end = nullptr;
		// ���Ļ��治���Է����������ڴ棬������ʵ��������
		size_t actualSize = CentralCache::GetInstance()->FetchToThreadCache(start, end, batchSize, alignSize);
		assert(actualSize != 0);

		if (actualSize == 1) {
			// Ϊ1��ֱ�ӾͰ��ڴ淵�أ����ù���ThreadCache
			assert(start == end);
		}
		else {
			// ��Ϊ1�Ͱ�ͷ��㷵�أ�ʣ�µĹ���ThreadCache
			_threadCache[index].Push(FreeList::Next(start), end);
		}

		return start;
	}

	// ������ͷ��ڴ����
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

// �̱߳��ش洢
thread_local ThreadCache* LocalThreadCache = nullptr;
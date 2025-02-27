#pragma once
#include "Span.h"
#include "Utils.h"

class CentralCache {
public:
	// ��ȡһ���ǿյ�span
	SpanNode* GetOneSpan(SpanList& list, size_t size)
	{
		return nullptr;
	}

	// �����Ļ����ȡһ�������Ķ����thread cache
	size_t FetchToThreadCache(void*& start, void*& end, size_t batchSize, size_t alignSize)
	{
		size_t index = Utils::Index(alignSize);

		// ��ͬ�߳̿���ͬʱ�������߳�ͬһ��SpanList���ʣ�������Ҫ����
		_centralCache[index]._mutex.lock();

		// ��alignSize??
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
	// CentralCache�ṹ��n��SpanList�Ĺ�ϣ�ṹ
	SpanList _centralCache[HARSH_SIZE];

// ��CentralCache���Ϊ����ģʽ������ʽ��
public:
	// ����ģʽ��ȡʵ��
	static CentralCache* GetInstance() {
		return &_centralCacheInstance;
	}

private:
	// ����ģʽ��ֹ�����͹���
	CentralCache() = delete;
	CentralCache(CentralCache& copy) = delete;

	// ����ģʽʵ��
	static CentralCache _centralCacheInstance;
};
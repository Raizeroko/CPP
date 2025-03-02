#pragma once
#include "Span.h"
#include "Utils.h"

class CentralCache {
public:
	SpanNode* GetOneSpan(SpanList& spanList, size_t alignSize);
	size_t FetchToThreadCache(void*& start, void*& end, size_t batchSize, size_t alignSize);
	void ReturnFromThreadCache(void* start, size_t alignSize);

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
	CentralCache(){}
	// ����ģʽ��ֹ��������
	CentralCache(const CentralCache& copy) = delete;
	void operator=(const CentralCache& copy) = delete;

	// ����ģʽʵ��
	static CentralCache _centralCacheInstance;
};



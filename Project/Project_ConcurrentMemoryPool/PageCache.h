#pragma once

#include "Span.h"
#include "Utils.h"
#include "RadixTree.h"
#include "FixedLengthMemoryPool.h"
#include <unordered_map>

class PageCache {
public:
	SpanNode* GetKPage(size_t k);
	void ReturnFromCentralCache(SpanNode* span);
	SpanNode* MapAddressToSpan(void* address);

private:
	// ��Ա����
	SpanList _pageCache[MAX_PAGE];
	// ��ϣ����ӳ���ϵ
	// std::unordered_map<PAGE_ID, SpanNode*> _pageIDToSpan;

	// ����������ӳ���ϵ
#ifdef _WIN64
	RadixTreeLevel3<64 - PAGE_SHIFT> _pageIDToSpan;

#elif _WIN32
	//RadixTreeLevel1<32 - PAGE_SHIFT> _pageIDToSpan;
	RadixTreeLevel2<32 - PAGE_SHIFT> _pageIDToSpan;
#endif

public:
	FixedLengthMemoryPool<SpanNode> _spanNodePool;
	std::mutex _pageMutex;


// ����ģʽ
public:
	// ��ȡʵ��
	static PageCache* GetInstance() {
		return &_pageCacheInstance;
	}
private:
	// ����ʵ��
	static PageCache _pageCacheInstance;
private:
	PageCache(){}
	// ��ֹ��������
	PageCache(const PageCache& copy) = delete;
	void operator=(const PageCache& copy) = delete;
};
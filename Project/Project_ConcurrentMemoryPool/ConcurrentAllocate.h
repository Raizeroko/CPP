#pragma once
#include "ThreadCache.h"
#include "PageCache.h"
#include "FixedLengthMemoryPool.h"

class ConcurrentAllocate {
public:
	static void* cmalloc(size_t allocateMemorySize) {
		// 大于256*1024字节的申请
		if (allocateMemorySize > MAX_SIZE) {
			size_t alignSize = Utils::AlignSize(allocateMemorySize);
			size_t numPages = alignSize >> PAGE_SHIFT;
			// 直接找PageCache申请，需要加锁
			PageCache::GetInstance()->_pageMutex.lock();
			SpanNode* bigSpan = PageCache::GetInstance()->GetKPage(numPages);
			PageCache::GetInstance()->_pageMutex.unlock();

			void* address = (void*)(bigSpan->_pageID << PAGE_SHIFT);
			return address;
		}
		else {
			if (LocalThreadCache == nullptr) {
				static FixedLengthMemoryPool<ThreadCache> threadCachePool;
				LocalThreadCache = threadCachePool.New();
			}
			std::cout << std::this_thread::get_id() << ":" << LocalThreadCache << std::endl;
			return LocalThreadCache->Allocate(allocateMemorySize);
		}
		
	}
	static void cfree(void* freeAddress) {
		assert(freeAddress);
		SpanNode* freeSpan = PageCache::GetInstance()->MapAddressToSpan(freeAddress);

		// 大内存释放
		if (freeSpan->_size > MAX_SIZE) {
			PageCache::GetInstance()->_pageMutex.lock();
			PageCache::GetInstance()->ReturnFromCentralCache(freeSpan);
			PageCache::GetInstance()->_pageMutex.unlock();
		}

		LocalThreadCache->Deallocate(freeAddress, freeSpan->_size);
	}
};

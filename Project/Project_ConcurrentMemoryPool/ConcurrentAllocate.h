#pragma once
#include "ThreadCache.h"


class ConcurrentAllocate {
	void* cmalloc(size_t allocateMemorySize) {
		if (LocalThreadCache == nullptr) {
			LocalThreadCache = new ThreadCache;
		}
		return LocalThreadCache->Allocate(allocateMemorySize);
	}
	void cmfree(void* freeMemory, size_t memorySize) {
		LocalThreadCache->Deallocate(freeMemory, memorySize);
	}
};

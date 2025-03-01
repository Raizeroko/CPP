#pragma once
#include "ThreadCache.h"

class ConcurrentAllocate {
public:
	static void* cmalloc(size_t allocateMemorySize) {
		if (LocalThreadCache == nullptr) {
			LocalThreadCache = new ThreadCache;
		}
		cout << std::this_thread::get_id() << ":" << LocalThreadCache << endl;
		return LocalThreadCache->Allocate(allocateMemorySize);
	}
	static void cmfree(void* freeAddress, size_t deallocateMemorySize) {
		assert(freeAddress);
		LocalThreadCache->Deallocate(freeAddress, deallocateMemorySize);
	}
};

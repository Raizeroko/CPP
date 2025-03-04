#pragma once
#include <cassert>
#include <iostream>

#ifdef _WIN32
	#include <windows.h>
#elif 
	//linux
#endif

// ThreadCache 和 CentralCache哈希表大小
const size_t HARSH_SIZE = 208;
// 申请最大字节数
const size_t MAX_SIZE = 256 * 1024;
// [2, 512]
const size_t UPPER = 512;
const size_t LOWER = 2;
// PageCache哈希表大小
const size_t MAX_PAGE = 129;
// 8*1024 = 2^13, 1page = 8*1024 = (8KB)
const size_t PAGE_SHIFT = 13;

class Utils {
public:
	// 哈希映射规则
	// [1,128]                  8byte对齐        freelist[0,16)
	// [128+1,1024]             16byte对齐       freelist[16,72) 
	// [1024+1,8*1024]          128byte对齐      freelist[72,128) 
	// [8*1024+1,64*1024]       1024byte对齐     freelist[128,184) 
	// [64*1024+1,256*1024]     8*1024byte对齐   freelist[184,208)

	static size_t AlignSize(size_t size)
	{
		if (size <= 128) {
			return _AlignSize(size, 8);
		}
		else if (size <= 1024) {
			return _AlignSize(size, 16);
		}
		else if (size <= 8 * 1024) {
			return _AlignSize(size, 128);
		}
		else if (size <= 64 * 1024) {
			return _AlignSize(size, 1024);
		}
		else if (size <= 256 * 1024) {
			return _AlignSize(size, 8*1024);
		}
		else {
			return _AlignSize(size, 1 << PAGE_SHIFT);
		}
	}

	static size_t Index(size_t bytes)
	{
		int IntervalSize[4] = { 16, 72, 128, 184 };

		size_t index = 0;
		if (bytes <= 128) {
			return _Index(bytes, 3);
		}
		else if (bytes <= 1024) {
			return _Index(bytes, 4) + IntervalSize[0];
		}
		else if (bytes <= 8 * 1024) {
			return _Index(bytes, 7) + IntervalSize[1];
		}
		else if (bytes <= 64 * 1024) {
			return _Index(bytes, 10) + IntervalSize[2];
		}
		else if (bytes <= 256 * 1024) {
			return _Index(bytes, 13) + IntervalSize[3];
		}
		else {
			assert(false);
			return -1;
		}

		return -1;
	}

	static size_t MoveBatchUpperLimit(size_t alignSize)
	{
		// 控制最大移动上界在[LOWER, UPPER]范围内
		size_t upper = MAX_SIZE / alignSize;
		if (upper < LOWER) {
			upper = LOWER;
		}
		if (upper > UPPER) {
			upper = UPPER;
		}
		return upper;
	}

	static size_t NumPage(size_t alignSize) {
		size_t upper = MoveBatchUpperLimit(alignSize);
		size_t numPage = upper * alignSize;
		numPage = numPage >> PAGE_SHIFT;
		if (numPage == 0)
			numPage = 1;
		return numPage;
	}


	static void* SystemAllocate(size_t kPages) {
#ifdef _WIN32
		void* newMemory = VirtualAlloc(NULL, kPages << 13, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#elif 
		//linux
#endif
		if (newMemory == nullptr) {
			throw std::bad_alloc();
		}
		return newMemory;
	}

	static void SystemDeallocate(void* ptr) {
		assert(ptr);
#ifdef _WIN32
		bool result = VirtualFree(ptr, 0, MEM_RELEASE);
#elif 
		//linux
#endif
		assert(result);
	}

private:
	static size_t _Index(size_t bytes, size_t alignShift) {
		// 不能这样计算，否则当(bytes < 2^alignShift)会返回-1；
		// return (bytes >> alignShift) - 1;
			
		// 向上对齐算法
		return ((bytes + (1 << alignShift) - 1) >> alignShift) - 1;
	}

	static size_t _AlignSize(size_t bytes, size_t alignByte) {
		// 自己解决
		// return ((size / alignByte) + 1) * alignByte;
		// 优化算法
		return ((bytes + alignByte - 1) & ~(alignByte - 1));
	}

};



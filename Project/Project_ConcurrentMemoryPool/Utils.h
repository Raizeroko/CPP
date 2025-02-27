#pragma once
#include <cassert>

#define HARSH_SIZE 208
#define MAX_SIZE 256*1024
#define UPPER 512
#define LOWER 2

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
			assert(false);
			return -1;
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
		return index - 1;
	}

	static size_t MoveBatchUpperLimit(size_t alignSize)
	{
		// 控制最大移动上界在[LOWER, UPPER]范围内
		size_t upper = MAX_SIZE / alignSize;
		if (upper < LOWER) {
			upper = LOWER;
		}
		if (upper < UPPER) {
			upper = UPPER;
		}
		return upper;
	}


private:
	static size_t _Index(size_t bytes, size_t alignShift) {
		// 不能这样计算，否则当(bytes < 2^alignShift)会返回-1；
		// return (bytes >> alignShift) - 1;
			
		// 向上对齐算法
		return ((bytes + (1 << alignShift)) >> alignShift) - 1;
	}

	static size_t _AlignSize(size_t bytes, size_t alignByte) {
		// 自己解决
		// return ((size / alignByte) + 1) * alignByte;
		// 优化算法
		return ((bytes + alignByte - 1) & ~(alignByte - 1));
	}

	





};



#pragma once
#include <cassert>

class FreeList {
public:
	FreeList()
		:_freeListHead(nullptr)
	{}

	void Push(void* pushNode)
	{
		// 头插
		Next(pushNode) = _freeListHead;
		_freeListHead = pushNode;
		_size += 1;
	}

	// 函数重载
	void Push(void* start, void* end, size_t pushSize)
	{
		
		Next(end) = _freeListHead;
		
		_freeListHead = start;
		_size += pushSize;

		/*size_t i = 0;
		void* tmp = _freeListHead;
		void* prev = nullptr;
		while (tmp) {
			prev = tmp;
			tmp = FreeList::Next(tmp);

			i++;
		}
		if (i != _size) {
			int x = 0;
		}*/
		
	}

	void* Pop()
	{
		// 头删
		void* popNode = _freeListHead;
		_freeListHead = *(void**)_freeListHead;
		_size -= 1;
		return popNode;

		
	}

	void* Pop(size_t popSize) {
		assert(popSize <= _size);

		// 头删popSize个结点
		void* end = _freeListHead;
		size_t curSize = 0;
		while (curSize < popSize - 1) {
			end = Next(end);
			curSize++;
		}
		void* start = _freeListHead;
		_freeListHead = Next(end);
		Next(end) = nullptr;
		_size -= popSize;

		

		return start;
	}



	bool Empty()
	{
		return _freeListHead == nullptr;
	}

	size_t& BatchSize() {
		return _batchSize;
	}

	static void*& Next(void* cur) {
		return *((void**)cur);
	}

	size_t Size() {
		return _size;
	}

private:
	void* _freeListHead;
	// 申请/归还批量
	size_t _batchSize = 1;
	// 当前_freeList中结点个数
	size_t _size = 0;
};
#pragma once
#include <cassert>

class FreeList {
public:
	FreeList()
		:_freeListHead(nullptr)
	{}

	void Push(void* pushNode)
	{
		// ͷ��
		Next(pushNode) = _freeListHead;
		_freeListHead = pushNode;
		_size += 1;
	}

	// ��������
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
		// ͷɾ
		void* popNode = _freeListHead;
		_freeListHead = *(void**)_freeListHead;
		_size -= 1;
		return popNode;

		
	}

	void* Pop(size_t popSize) {
		assert(popSize <= _size);

		// ͷɾpopSize�����
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
	// ����/�黹����
	size_t _batchSize = 1;
	// ��ǰ_freeList�н�����
	size_t _size = 0;
};
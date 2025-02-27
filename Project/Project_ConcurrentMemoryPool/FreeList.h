#pragma once

class FreeList {
public:
	FreeList()
		:_freeListHead(nullptr)
	{}

	void Push(void* pushNode)
	{
		// Í·²å
		Next(pushNode) = _freeListHead;
		_freeListHead = pushNode;
	}

	void Push(void* start, void* end)
	{
		// Í·²å
		Next(end) = _freeListHead;
		_freeListHead = start;
	}

	void* Pop()
	{
		// Í·É¾
		void* popNode = _freeListHead;
		_freeListHead = *(void**)_freeListHead;
		return popNode;
	
	}
	bool Empty()
	{
		return _freeListHead == nullptr;
	}

	size_t& FetchBatch() {
		return _fetchBatch;
	}

	static void*& Next(void* cur) {
		return *(void**)cur;
	}

private:
	void* _freeListHead;
	size_t _fetchBatch = 1;
};
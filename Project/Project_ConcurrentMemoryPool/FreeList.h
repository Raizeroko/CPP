#pragma once

class FreeList {
public:
	FreeList()
		:_freeListHead(nullptr)
	{}

	void Push(void* pushNode)
	{
		// Í·²å
		*((void**)pushNode) = _freeListHead;
		_freeListHead = pushNode;
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

private:
	void* _freeListHead;
};
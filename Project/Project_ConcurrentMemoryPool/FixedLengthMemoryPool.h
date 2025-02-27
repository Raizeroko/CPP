#pragma once

#include <iostream>

#define MEMORY_LENGTH 1024*8 //256KB

template<class T>
class FixedLengthMemoryPool {
public:
	FixedLengthMemoryPool()
		:_memory(nullptr)
		,_freeList(nullptr)
		,_remainSize(0)
	{}

	T* New()
	{
		T* object;
		if (_freeList) {
			object = (T*)_freeList;
			_freeList = *((void**)_freeList);
		}
		else {
			// 分配的内存至少能存储一个指针
			size_t objectSize = sizeof(T) < sizeof(void*) ? sizeof(void*) : sizeof(T);
			if (_remainSize < objectSize) {
				// 不充足内存
				_memory = (char*)malloc(MEMORY_LENGTH);
				if (_memory == nullptr) {
					throw std::bad_alloc();
				}
				_remainSize = MEMORY_LENGTH;
			}
			// 充足内存
			object = (T*)_memory;
			_memory += objectSize;
			_remainSize -= objectSize;
		}
		
		// 已有空间，使用定位new在该空间构造对象
		new(object)T();

		return object;
		
	}

	void Delete(T* object)
	{
		object->~T();

		*((void**)object) = _freeList;
		_freeList = (void*)object;
	}


private:
	char* _memory;		// 定长内存池
	size_t _remainSize;	// 内存池剩余大小
	void* _freeList;	// 使用过的内存挂接链表
};



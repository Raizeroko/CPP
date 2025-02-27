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
			// ������ڴ������ܴ洢һ��ָ��
			size_t objectSize = sizeof(T) < sizeof(void*) ? sizeof(void*) : sizeof(T);
			if (_remainSize < objectSize) {
				// �������ڴ�
				_memory = (char*)malloc(MEMORY_LENGTH);
				if (_memory == nullptr) {
					throw std::bad_alloc();
				}
				_remainSize = MEMORY_LENGTH;
			}
			// �����ڴ�
			object = (T*)_memory;
			_memory += objectSize;
			_remainSize -= objectSize;
		}
		
		// ���пռ䣬ʹ�ö�λnew�ڸÿռ乹�����
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
	char* _memory;		// �����ڴ��
	size_t _remainSize;	// �ڴ��ʣ���С
	void* _freeList;	// ʹ�ù����ڴ�ҽ�����
};



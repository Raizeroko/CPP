#pragma once

#include <iostream>
#include <vector>
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






// Text Code
//using std::cout;
//using std::cin;
//using std::endl;
//
//struct TreeNode {
//	int _val; TreeNode* _left; TreeNode* _right;
//	TreeNode()
//		:_val(0)
//		, _left(nullptr)
//		, _right(nullptr) {}
//};
//
//void TestFixedLengthMemoryPool() {
//	// 申请释放的轮次
//	const size_t Rounds = 3;
//	// 每轮申请释放多少次
//	const size_t N = 100000;
//	size_t begin1 = clock();
//	std::vector<TreeNode*> v1; v1.reserve(N);
//	for (size_t j = 0; j < Rounds; ++j) {
//		for (int i = 0; i < N; ++i) {
//			v1.push_back(new TreeNode);
//		}
//		for (int i = 0; i < N; ++i) {
//			delete v1[i];
//		} v1.clear();
//	}
//	size_t end1 = clock();
//	FixedLengthMemoryPool<TreeNode> TNPool;
//	size_t begin2 = clock();
//	std::vector<TreeNode*> v2;
//	v2.reserve(N);
//	for (size_t j = 0; j < Rounds; ++j)
//	{
//		for (int i = 0; i < N; ++i) {
//			v2.push_back(TNPool.New());
//		}
//		for (int i = 0; i < N; ++i) {
//			TNPool.Delete(v2[i]);
//		}
//		v2.clear();
//	}
//	size_t end2 = clock();
//	cout << "new cost time:" << end1 - begin1 << endl;
//	cout << "object pool cost time:" << end2 - begin2 << endl;
//}


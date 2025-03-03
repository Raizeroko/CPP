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
//	// �����ͷŵ��ִ�
//	const size_t Rounds = 3;
//	// ÿ�������ͷŶ��ٴ�
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


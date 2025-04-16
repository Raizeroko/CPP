#include "FixedLengthMemoryPool.h"
#include "Utils.h"
#include "ConcurrentAllocate.h"


#include <iostream>
#include <vector>

using std::cout;
using std::endl;


// TestCode
void TestAlignSize() {
	// Utils utils;

	// 测试 AlignSize 方法
	assert(Utils::AlignSize(8) == 8); // 8 byte对齐
	assert(Utils::AlignSize(128) == 128); // 16 byte对齐
	assert(Utils::AlignSize(150) == 160); // 16 byte对齐
	assert(Utils::AlignSize(1025) == 1152); // 128 byte对齐
	assert(Utils::AlignSize(2000) == 2048); // 1024 byte对齐
	assert(Utils::AlignSize(100000) == 106496); // 8*1024 byte对齐

	std::cout << "AlignSize test passed!" << std::endl;
}

void TestIndex() {
	//Utils utils;

	// 测试 Index 方法
	assert(Utils::Index(8) == 0); // 在第一个区间
	assert(Utils::Index(100) == 12); // 在第一个区间
	assert(Utils::Index(500) == 47); // 在第二个区间
	assert(Utils::Index(1500) == 83); // 在第三个区间
	assert(Utils::Index(50000) == 176); // 在第四个区间
	assert(Utils::Index(150000) == 202); // 在第五个区间

	std::cout << "Index test passed!" << std::endl;
}


void TestAllocationProcess() {
	ConcurrentAllocate ca;
	ca.cmalloc(5);
}


void Alloc1()
{
	for (size_t i = 0; i < 5; ++i)
	{
		void* ptr = ConcurrentAllocate::cmalloc(6);
	}
}

void Alloc2()
{
	for (size_t i = 0; i < 5; ++i)
	{
		void* ptr = ConcurrentAllocate::cmalloc(7);
	}
}

void TLSTest()
{
	std::thread t1(Alloc1);

	std::thread t2(Alloc2);
	t1.join();

	t2.join();
}

void TestConcurrentAlloc1()
{
	void* p1 = ConcurrentAllocate::cmalloc(6);
	void* p2 = ConcurrentAllocate::cmalloc(8);
	void* p3 = ConcurrentAllocate::cmalloc(1);
	void* p4 = ConcurrentAllocate::cmalloc(7);
	void* p5 = ConcurrentAllocate::cmalloc(8);

	cout << p1 << endl;
	cout << p2 << endl;
	cout << p3 << endl;
	cout << p4 << endl;
	cout << p5 << endl;

	ConcurrentAllocate::cfree(p1);
	ConcurrentAllocate::cfree(p2);
	ConcurrentAllocate::cfree(p3);
	ConcurrentAllocate::cfree(p4);
	ConcurrentAllocate::cfree(p5);



}

void TestConcurrentAlloc2()
{
	for (size_t i = 0; i < 7; ++i)
	{
		void* p1 = ConcurrentAllocate::cmalloc(16);
		cout << p1 << endl;
	}

	void* p2 = ConcurrentAllocate::cmalloc(8);
	cout << p2 << endl;
}



void MultiThreadAlloc1()
{
	std::vector<void*> v;
	for (size_t i = 0; i < 1024; ++i)
	{
		void* ptr = ConcurrentAllocate::cmalloc(6);
		v.push_back(ptr);
	}

	for (auto e : v)
	{
		ConcurrentAllocate::cfree(e);
	}
}

void MultiThreadAlloc2()
{
	std::vector<void*> v;
	for (size_t i = 0; i < 1024; ++i)
	{
		void* ptr = ConcurrentAllocate::cmalloc(16);
		v.push_back(ptr);
	}
	for (auto e : v)
	{
		ConcurrentAllocate::cfree(e);
	}
}

void TestMultiThread()
{
	std::thread t1(MultiThreadAlloc1);
	std::thread t2(MultiThreadAlloc2);

	t1.join();
	t2.join();
}



//int main() {
//	//TestFixedLengthMemoryPool();
//	//TestAlignSize();
//	//TestIndex();
//	//TestAllocationProcess();
//	//TLSTest();
//	//TestConcurrentAlloc1();
//	//TestConcurrentAlloc2();
//	//TestMultiThread();
//}



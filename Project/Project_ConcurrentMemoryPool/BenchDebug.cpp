#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <atomic>
#include <functional>
#include "ConcurrentAllocate.h"
using namespace std;

void BenchmarkMalloc(size_t ntimes, size_t nworks, size_t rounds)
{
	std::vector<std::thread> vthread(nworks);
	std::atomic<size_t> malloc_costtime = 0;
	std::atomic<size_t> free_costtime = 0;

	for (size_t k = 0; k < nworks; ++k)
	{
		vthread[k] = std::thread([&, k]() {
			std::vector<void*> v;
			v.reserve(ntimes);

			for (size_t j = 0; j < rounds; ++j)
			{
				size_t begin1 = clock();
				for (size_t i = 0; i < ntimes; i++)
				{
					v.push_back(malloc(16));
					//v.push_back(malloc((16 + i) % 8192 + 1));
				}
				size_t end1 = clock();

				size_t begin2 = clock();
				for (size_t i = 0; i < ntimes; i++)
				{
					free(v[i]);
				}
				size_t end2 = clock();
				v.clear();

				malloc_costtime += (end1 - begin1);
				free_costtime += (end2 - begin2);
			}
			});
	}

	for (auto& t : vthread)
	{
		t.join();
	}

	printf("%u个线程并发执行%u轮次，每轮次malloc %u次: 花费：%u ms\n",
		nworks, rounds, ntimes, malloc_costtime.load());

	printf("%u个线程并发执行%u轮次，每轮次free %u次: 花费：%u ms\n",
		nworks, rounds, ntimes, free_costtime.load());

	printf("%u个线程并发malloc&free %u次，总计花费：%u ms\n",
		nworks, nworks * rounds * ntimes, malloc_costtime.load() + free_costtime.load());
}


 //单轮次申请释放次数 线程数 轮次
void BenchmarkConcurrentMalloc(size_t ntimes, size_t nworks, size_t rounds)
{
	std::vector<std::thread> vthread(nworks);
	std::atomic<size_t> malloc_costtime = 0;
	std::atomic<size_t> free_costtime = 0;

	for (size_t k = 0; k < nworks; ++k)
	{
		vthread[k] = std::thread([&]() {
			std::vector<void*> v;
			v.reserve(ntimes);

			for (size_t j = 0; j < rounds; ++j)
			{
				size_t begin1 = clock();
				for (size_t i = 0; i < ntimes; i++)
				{
					v.push_back(ConcurrentAllocate::cmalloc(16));
					//v.push_back(ConcurrentAlloc((16 + i) % 8192 + 1));
				}
				size_t end1 = clock();

				size_t begin2 = clock();
				for (size_t i = 0; i < ntimes; i++)
				{
					ConcurrentAllocate::cfree(v[i]);
				}
				size_t end2 = clock();
				v.clear();

				malloc_costtime += (end1 - begin1);
				free_costtime += (end2 - begin2);
			}
			});
	}

	for (auto& t : vthread)
	{
		t.join();
	}

	printf("%u个线程并发执行%u轮次，每轮次concurrent alloc %u次: 花费：%u ms\n",
		nworks, rounds, ntimes, malloc_costtime.load());

	printf("%u个线程并发执行%u轮次，每轮次concurrent dealloc %u次: 花费：%u ms\n",
		nworks, rounds, ntimes, free_costtime.load());

	printf("%u个线程并发concurrent alloc&dealloc %u次，总计花费：%u ms\n",
		nworks, nworks * rounds * ntimes, malloc_costtime.load() + free_costtime.load());
}


 //排除是否是多线程导致的问题
//void BenchmarkConcurrentMalloc(size_t ntimes, size_t nworks, size_t rounds)
//{
//	size_t malloc_costtime = 0;
//	size_t free_costtime = 0;
//
//	for (size_t k = 0; k < nworks; ++k)
//	{
//		std::vector<void*> v;
//		v.reserve(ntimes);
//
//		for (size_t j = 0; j < rounds; ++j)
//		{
//			size_t begin1 = clock();
//			for (size_t i = 0; i < ntimes; i++)
//			{
//				/*v.push_back(ConcurrentAllocate::cmalloc(16));*/
//				//v.push_back(ConcurrentAlloc((16 + i) % 8192 + 1));
//				void* ptr = ConcurrentAllocate::cmalloc(16);
//				assert(ptr != nullptr); // 检查分配的内存非空
//				v.push_back(ptr);
//			}
//			size_t end1 = clock();
//
//			size_t begin2 = clock();
//			for (size_t i = 0; i < ntimes; i++)
//			{
//				ConcurrentAllocate::cfree(v[i]);
//			}
//			size_t end2 = clock();
//			v.clear();
//
//			malloc_costtime += (end1 - begin1);
//			free_costtime += (end2 - begin2);
//		}
//	}
//
//	printf("单线程执行%u轮次，每轮次concurrent alloc %u次: 花费：%u ms\n",
//		rounds, ntimes, malloc_costtime);
//
//	printf("单线程执行%u轮次，每轮次concurrent dealloc %u次: 花费：%u ms\n",
//		rounds, ntimes, free_costtime);
//
//	printf("单线程concurrent alloc&dealloc %u次，总计花费：%u ms\n",
//		nworks * rounds * ntimes, malloc_costtime + free_costtime);
//}


//int main()
//{
//	size_t n = 10000;
//	cout << "==========================================================" << endl;
//	BenchmarkMalloc(n, 4, 10);
//
//	cout << endl << endl;
//
//	cout << "==========================================================" << endl;
//	BenchmarkConcurrentMalloc(n, 4, 10);
//
//	return 0;
//}
#pragma 
#include <thread>

#include "FreeList.h"
#include "Utils.h"


class ThreadCache {
public:
	// ������ͷ��ڴ����
	void* Allocate(size_t allocateMemorySize);
	void Deallocate(void* ptr, size_t allocateMemorySize);


	void* FetchFromCentralCache(size_t index, size_t alignSize);
	void ReturnToCentralCache(FreeList& returnList, size_t allocateMemorySize);
private:
	FreeList _threadCache[HARSH_SIZE];
};

// �̱߳��ش洢
static thread_local ThreadCache* LocalThreadCache = nullptr;
// extern thread_local ThreadCache* LocalThreadCache;
 //static _declspec(thread) ThreadCache* LocalThreadCache = nullptr;



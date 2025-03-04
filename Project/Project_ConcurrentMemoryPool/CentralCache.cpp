#include "CentralCache.h"
#include "PageCache.h"

// 静态成员变量，类内声明，类外定义
CentralCache CentralCache::_centralCacheInstance;

// 获取一个非空的span(一个Span可能放了不止1个Page)
SpanNode* CentralCache::GetOneSpan(SpanList& spanList, size_t alignSize)
{
	assert(alignSize > 0 && alignSize < MAX_SIZE);

	// 检查CentralCache[index]有无可分配Span
	SpanNode* spanCur = spanList.Begin();
	while (spanCur != spanList.End()) {
		if (spanCur->_freeList != nullptr) {
			return spanCur;
		}
		spanCur = spanCur->_next;
	}

	// 从PageCache获取k页缓存，暂时不需要对中心缓存操作，所以释放锁，其他线程不仅可以归还内存，同时也能进行上面的分配。
 	spanList._mutex.unlock();
	size_t numPage = Utils::NumPage(alignSize);

	// 可能有多个线程同时从PageCache获取内存
	PageCache::GetInstance()->_pageMutex.lock();
	// 从PageCache获取K页的内存信息（页号，页数）
	SpanNode* kPage = PageCache::GetInstance()->GetKPage(numPage);
	kPage->_isUse = true;
	kPage->_size = alignSize;
	PageCache::GetInstance()->_pageMutex.unlock();

	// 根据页号获取申请的内存地址,用char*方便利用alignSize决定分割地址
	kPage->_freeList = (void*)(kPage->_pageID << PAGE_SHIFT);
	char* cur = (char*)kPage->_freeList;
	size_t bytes = numPage << PAGE_SHIFT;
	char* end = cur + bytes;
	char* next = cur + alignSize;
	// 连接PageCache申请的内存
	while (cur < end - alignSize) {
		FreeList::Next(cur) = next;
		cur = next;
		next = next + alignSize;
	}
	// cur = end - alignSize, 对最后的尾指空
	FreeList::Next(cur) = nullptr;

	// 初始化kPage->_size大小
	kPage->_size = alignSize;

	// 要对中心缓存操作，所以加锁
	spanList._mutex.lock();

	//  在链表初始化完成后打印链表长度
	size_t debugLength = 0;
	void* debugCur = kPage->_freeList;
	while (debugCur) {
		debugCur = FreeList::Next(debugCur);
		debugLength++;
	}
	size_t expectedLength = (numPage << PAGE_SHIFT) / alignSize;
	/*if (debugLength != expectedLength) {
		printf("Debug: GetOneSpan - Linked list length mismatch. Expected: %zu, Actual: %zu\n", expectedLength, debugLength);
	}*/

	// 在 _centralCache[index] 插入前检查链表
	/*if (kPage->_freeList == nullptr) {
		printf("Debug: GetOneSpan - kPage->_freeList is null before inserting into _centralCache.\n");
	}*/
	// 将连接好的内存放入中心缓存中

	//DebugPrintSpanList(spanList);
	spanList.PushFront(kPage);
	//DebugPrintSpanList(spanList);
	
	return kPage;
}

// 从中心缓存获取一定数量的对象给thread cache
size_t CentralCache::FetchToThreadCache(void*& start, void*& end, size_t batchSize, size_t alignSize)
{

	assert(batchSize > 0 && batchSize <= UPPER);
	assert(alignSize > 0 && alignSize <= MAX_SIZE);
	size_t index = Utils::Index(alignSize);

	// 不同线程可能同时对中心缓存同一个SpanList访问，所以需要加锁
	_centralCache[index]._mutex.lock();

	// 传alignSize
	SpanNode* spanHead = GetOneSpan(_centralCache[index], alignSize);
	assert(spanHead);
	assert(spanHead->_freeList);
	start = spanHead->_freeList;
	end = start;
	size_t actualSize = 1;

	// 分割
	while (FreeList::Next(end) != nullptr && actualSize < batchSize) {
		actualSize++;
		end = FreeList::Next(end);
	}
	spanHead->_freeList = FreeList::Next(end);
	FreeList::Next(end) = nullptr;
	spanHead->_useCount += actualSize;
	_centralCache[index]._mutex.unlock();

	/*size_t debugLength = 0;
	void* debugCur = start;
	while (debugCur) {
		debugCur = FreeList::Next(debugCur);
		debugLength++;
	}
	if (debugLength != actualSize) {
		printf("Debug: FetchToThreadCache - Mismatch in actualSize and linked list length.\n");
	}*/

	return actualSize;
}


void CentralCache::ReturnFromThreadCache(void* start, size_t alignSize) {
	assert(start);
	assert(alignSize > 0 && alignSize < MAX_SIZE);
	// 将ThreadCache返回的批量结点挂回CentralCache
	size_t index = Utils::Index(alignSize);

	// 要向CentralCache插入结点需要加锁
	_centralCache[index]._mutex.lock();


	while (start) {
		// 归还给哪一个Span？ (要放到循环内！！！！）
		SpanNode* returnSpan = PageCache::GetInstance()->MapAddressToSpan(start);

		// 头插到该span的freeList;
		void* next = FreeList::Next(start);
		FreeList::Next(start) = returnSpan->_freeList;
		returnSpan->_freeList = start;
		returnSpan->_useCount--;
		if (returnSpan->_useCount == 0) {
			// 从CentralCache分离该span

			/*
			_centralCache->Erase(returnSpan); 这种写法为什么不会报错？？？？？
			数组名退化为指针：当使用 _centralCache-> 时，数组名 _centralCache 会隐式退化为指向数组首元素的指针
			(&_centralCache[0])->Erase(returnSpan);
			*/ 

			_centralCache[index].Erase(returnSpan);  
			// PageCache能通过_pageID找到地址，不需要管理_freeList的连接，所以直接指空
			returnSpan->_freeList = nullptr;
			returnSpan->_next = nullptr;
			returnSpan->_prev = nullptr;

			

			// 归还到PageCache解除CentralCache的锁，加上PageCache的锁
			_centralCache[index]._mutex.unlock();
			PageCache::GetInstance()->_pageMutex.lock();
			PageCache::GetInstance()->ReturnFromCentralCache(returnSpan);
			// 回到CentralCache解除PageCache的锁，加上CentralChe的锁
			PageCache::GetInstance()->_pageMutex.unlock();
			_centralCache[index]._mutex.lock();
		}
		start = next;
	}
	_centralCache[index]._mutex.unlock();

}

// 重写了
//void CentralCache::ReturnFromCentralCache(void* start, size_t alignSize) {
//	// 将ThreadCache返回的批量结点挂回CentralCache
//	size_t index = Utils::Index(alignSize);
//
//	while (start) {
//
//		void* next = Next(start);
//
//		// 返给哪个span??
//		SpanNode* span = new SpanNode;
//		FreeList::Next(start) = span->_freeList;
//		span->_freeList = start;
//		span->_useCount--;
//		
//		// 该span结点已经全部挂回，由CentralCache归还给ThreadCache
//		if (span->_useCount == 0) {
//			_centralCache->Erase(span);
//			span->_next = nullptr;
//			span->_prev = 0;
//			span->_freeList = nullptr;
//
//			PageCache::GetInstance()->ReturnToPageCache(span);
//
//			
//		}
//		start = next;
//	}
//
//}


// 测试：打印 SpanList 链表状态
//void CentralCache::DebugPrintSpanList(SpanList& spanList) {
//	printf("Debug: SpanList State:\n");
//
//	SpanNode* current = spanList.Begin();
//	while (current != spanList.End()) {
//		printf("  SpanNode - pageID: %llu, pageNum: %zu, freeList: %p, isUse: %d\n",
//			current->_pageID, current->_pageNum, current->_freeList, current->_isUse);
//		current = current->_next;
//	}
//	printf("End of SpanList\n");
//}




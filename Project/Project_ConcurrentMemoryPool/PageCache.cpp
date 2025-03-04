#include "PageCache.h"

// 静态成员变量，类内声明，类外定义
PageCache PageCache::_pageCacheInstance;


SpanNode* PageCache::GetKPage(size_t k) {
	assert(k > 0);

	if (k >= MAX_PAGE) {
		void* newMemory = Utils::SystemAllocate(k);
		SpanNode* bigSpan = _spanNodePool.New();
		bigSpan->_pageNum = k;
		bigSpan->_pageID = (PAGE_ID)newMemory >> PAGE_SHIFT;
		bigSpan->_isUse = true;
		// 哈希建立映射
		// _pageIDToSpan[bigSpan->_pageID] = bigSpan;
		// 基数树建立映射
		_pageIDToSpan.set(bigSpan->_pageID, bigSpan);

		return bigSpan;
	}

	// 当前页缓存第k个不为空
	if (!_pageCache[k].Empty()) {
		// 测试
		//DebugPrintPageCache2(_pageCache[k]);
		//
		SpanNode* splitSpan = _pageCache[k].PopFront();
		//测试
		//DebugPrintPageCache2(_pageCache[k]);
		//

		for (int i = 0; i < splitSpan->_pageNum; i++) {
			// 哈希建立映射
			//_pageIDToSpan[splitSpan->_pageID + i] = splitSpan;
			// 基数树建立映射
			_pageIDToSpan.set(splitSpan->_pageID + i, splitSpan);

		}
		return splitSpan;
	}

	// 从第k个位置往下找到不为的空位置
	for (size_t i = k; i < MAX_PAGE; i++) {
		if (!_pageCache[i].Empty()) {
			// 分割
			SpanNode* RemainSpan = _pageCache[i].PopFront();
			//assert((RemainSpan->_pageID & ((1 << PAGE_SHIFT))) == 0 && "PageID misaligned before split");
			SpanNode* splitSpan = _spanNodePool.New();
			// 切分后页数更新
			splitSpan->_pageNum = k;
			RemainSpan->_pageNum -= k;
			// 切分后页号更新（页号是找到所申请内存的地址映射）
			splitSpan->_pageID = RemainSpan->_pageID;
			RemainSpan->_pageID += k;
			_pageCache[RemainSpan->_pageNum].PushFront(RemainSpan);

			// 映射管理
			// bigSpan只由PageCache管理，所以只需要将该Span页区间首位映射到该Span，方便pageCache合并连续Span
			// 哈希建立映射
			// _pageIDToSpan[RemainSpan->_pageID] = RemainSpan;
			// _pageIDToSpan[RemainSpan->_pageID + RemainSpan->_pageNum - 1] = RemainSpan;
			// 基数树建立映射
			_pageIDToSpan.set(RemainSpan->_pageID, RemainSpan);
			_pageIDToSpan.set(RemainSpan->_pageID + RemainSpan->_pageNum - 1, RemainSpan);


			// 取出的所有页都要进行映射，释放时才能找到对应Span
			for (int i = 0; i < splitSpan->_pageNum; i++) {
				// 哈希建立映射
				//_pageIDToSpan[splitSpan->_pageID + i] = splitSpan;
				// 基数树建立映射
				_pageIDToSpan.set(splitSpan->_pageID + i, splitSpan);
			}
			// 挂到CentralCache表示当前Span被使用

			// 测试：在 RemainSpan 和 splitSpan 的生成后，添加检查和打印。
			/*if (RemainSpan->_pageNum + splitSpan->_pageNum != i) {
				printf("Debug: PageCache split error! RemainSpan pageNum: %zu, splitSpan pageNum: %zu\n",
					RemainSpan->_pageNum, splitSpan->_pageNum);
			}*/
			// 测试：确保 splitSpan 和 RemainSpan 的页号范围正确映射。
			/*for (int i = 0; i < splitSpan->_pageNum; i++) {
				assert(_pageIDToSpan[splitSpan->_pageID + i] == splitSpan;
			}
			for (int i = 0; i < RemainSpan->_pageNum; i++) {
				assert(_pageIDToSpan[RemainSpan->_pageID + i] == RemainSpan);
			}*/
			/*printf("Debug: RemainSpan - pageID: %llu, pageNum: %zu\n", RemainSpan->_pageID, RemainSpan->_pageNum);
			printf("Debug: splitSpan - pageID: %llu, pageNum: %zu\n", splitSpan->_pageID, splitSpan->_pageNum);
			for (int i = 0; i < RemainSpan->_pageNum; i++) {
				printf("Debug: _pageIDToSpan[%llu] = %p\n", RemainSpan->_pageID + i, _pageIDToSpan[RemainSpan->_pageID + i]);
			}
			for (int i = 0; i < splitSpan->_pageNum; i++) {
				printf("Debug: _pageIDToSpan[%llu] = %p\n", splitSpan->_pageID + i, _pageIDToSpan[splitSpan->_pageID + i]);
			}
			assert((RemainSpan->_pageID & ((1 << PAGE_SHIFT))) == 0);
			assert((splitSpan->_pageID & ((1 << PAGE_SHIFT) - 1)) == 0);*/
			//
			
			return splitSpan;
		}
	}
	// 从堆空间申请新的内存
	void* newMemory = Utils::SystemAllocate(MAX_PAGE - 1);

	// 测试：确认系统分配内存的大小和起始地址正确
	//printf("Debug: SystemAllocate - newMemory: %p, size: %zu\n", newMemory, MAX_PAGE - 1);
	/*assert(((uintptr_t)newMemory & ((1 << PAGE_SHIFT) - 1)) == 0);
	printf("Debug: SystemAllocate - newMemory is aligned\n");*/
	//assert(((PAGE_ID)newMemory & ((1 << PAGE_SHIFT))) == 0 && "SystemAllocate returned misaligned address");
	//

	SpanNode* newSpan = _spanNodePool.New();
	newSpan->_pageNum = MAX_PAGE - 1;
	newSpan->_pageID = (PAGE_ID)newMemory >> PAGE_SHIFT;
	_pageCache[MAX_PAGE - 1].PushFront(newSpan);
	return GetKPage(k);
}

void PageCache::ReturnFromCentralCache(SpanNode* returnSpan) {
	assert(returnSpan);
	if (returnSpan->_pageNum >= MAX_PAGE) {
		void* freeAddress = (void*)(returnSpan->_pageID << PAGE_SHIFT);
		Utils::SystemDeallocate(freeAddress);
		_spanNodePool.Delete(returnSpan);
		return;
	}

	// 合并检查
	// 归还Span的前一个Span是否在PageCache中
	while (1) {
		//auto prev = _pageIDToSpan.find(returnSpan->_pageID - 1);
		//// 没找到，结束合并
		//if (prev == _pageIDToSpan.end()) {
		//	break;
		//}
		//SpanNode* prevSpan = prev->second;
		SpanNode* prevSpan = (SpanNode*)_pageIDToSpan.find(returnSpan->_pageID - 1);
		if (prevSpan == nullptr) {
			break;
		}

		// 如果该span在使用，结束合并
		if (prevSpan->_isUse == true) {
			break;
		}
		// 如果超出Page限制，结束合并
		if (prevSpan->_pageNum + returnSpan->_pageNum > MAX_PAGE) {
			break;
		}
		_pageCache[prevSpan->_pageNum].Erase(prevSpan);
		returnSpan->_pageID = prevSpan->_pageID;
		returnSpan->_pageNum += prevSpan->_pageNum;
		_spanNodePool.Delete(prevSpan);
	}
	while (1) {
		// 哈希建立映射
		//auto next = _pageIDToSpan.find(returnSpan->_pageID + returnSpan->_pageNum);
		//// 没找到，结束合并
		//if (next == _pageIDToSpan.end()) {
		//	break;
		//}
		//SpanNode* nextSpan = next->second;
		// 基数树建立映射
		SpanNode* nextSpan = (SpanNode*)_pageIDToSpan.find(returnSpan->_pageID + returnSpan->_pageNum);
		if (nextSpan == nullptr) {
			break;
		}
	
		// 如果该span在使用，结束合并
		if (nextSpan->_isUse == true) {
			break;
		}
		// 如果超出Page限制，结束合并
		if (nextSpan->_pageNum + returnSpan->_pageNum > MAX_PAGE) {
			break;
		}
		_pageCache[nextSpan->_pageNum].Erase(nextSpan);
		returnSpan->_pageNum += nextSpan->_pageNum;
		_spanNodePool.Delete(nextSpan);
	}

	_pageCache[returnSpan->_pageNum].PushFront(returnSpan);
	// 合并完才能更改为是否使用
	returnSpan->_isUse = false;
	// 哈希建立映射
	//_pageIDToSpan[returnSpan->_pageID] = returnSpan;
	//_pageIDToSpan[returnSpan->_pageID + returnSpan->_pageNum - 1] = returnSpan;
	// 基数树建立映射
	_pageIDToSpan.set(returnSpan->_pageID, returnSpan);
	_pageIDToSpan.set(returnSpan->_pageID + returnSpan->_pageNum - 1, returnSpan);
	
} 

// 地址映射Span
SpanNode* PageCache::MapAddressToSpan(void* address) {
	assert(address);
	size_t pageID = (PAGE_ID)address >> PAGE_SHIFT;
	// 哈希建立映射
	// std::unique_lock<std::mutex> lock(_pageMutex);
	/*auto map = _pageIDToSpan.find(pageID);
	if (map != _pageIDToSpan.end()) {
		return map->second;
	}
	else {
		assert(false);
		return nullptr;
	}*/
	// 基数树建立映射
	SpanNode* mapNode = (SpanNode*)_pageIDToSpan.find(pageID);
	assert(mapNode);
	return mapNode;

}

// 测试代码
//void PageCache::DebugPrintPageCache2(SpanList& pageCache) {
//	SpanNode* current = pageCache.Begin();
//	while (current != pageCache.End()) {
//		printf("  SpanNode - pageID: %llu, pageNum: %zu, isUse: %d\n",
//			current->_pageID, current->_pageNum, current->_isUse);
//		current = current->_next;
//	}
//	printf("End of PageCache\n");
//}


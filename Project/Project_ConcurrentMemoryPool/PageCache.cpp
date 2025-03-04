#include "PageCache.h"

// ��̬��Ա�������������������ⶨ��
PageCache PageCache::_pageCacheInstance;


SpanNode* PageCache::GetKPage(size_t k) {
	assert(k > 0);

	if (k >= MAX_PAGE) {
		void* newMemory = Utils::SystemAllocate(k);
		SpanNode* bigSpan = _spanNodePool.New();
		bigSpan->_pageNum = k;
		bigSpan->_pageID = (PAGE_ID)newMemory >> PAGE_SHIFT;
		bigSpan->_isUse = true;
		// ��ϣ����ӳ��
		// _pageIDToSpan[bigSpan->_pageID] = bigSpan;
		// ����������ӳ��
		_pageIDToSpan.set(bigSpan->_pageID, bigSpan);

		return bigSpan;
	}

	// ��ǰҳ�����k����Ϊ��
	if (!_pageCache[k].Empty()) {
		// ����
		//DebugPrintPageCache2(_pageCache[k]);
		//
		SpanNode* splitSpan = _pageCache[k].PopFront();
		//����
		//DebugPrintPageCache2(_pageCache[k]);
		//

		for (int i = 0; i < splitSpan->_pageNum; i++) {
			// ��ϣ����ӳ��
			//_pageIDToSpan[splitSpan->_pageID + i] = splitSpan;
			// ����������ӳ��
			_pageIDToSpan.set(splitSpan->_pageID + i, splitSpan);

		}
		return splitSpan;
	}

	// �ӵ�k��λ�������ҵ���Ϊ�Ŀ�λ��
	for (size_t i = k; i < MAX_PAGE; i++) {
		if (!_pageCache[i].Empty()) {
			// �ָ�
			SpanNode* RemainSpan = _pageCache[i].PopFront();
			//assert((RemainSpan->_pageID & ((1 << PAGE_SHIFT))) == 0 && "PageID misaligned before split");
			SpanNode* splitSpan = _spanNodePool.New();
			// �зֺ�ҳ������
			splitSpan->_pageNum = k;
			RemainSpan->_pageNum -= k;
			// �зֺ�ҳ�Ÿ��£�ҳ�����ҵ��������ڴ�ĵ�ַӳ�䣩
			splitSpan->_pageID = RemainSpan->_pageID;
			RemainSpan->_pageID += k;
			_pageCache[RemainSpan->_pageNum].PushFront(RemainSpan);

			// ӳ�����
			// bigSpanֻ��PageCache��������ֻ��Ҫ����Spanҳ������λӳ�䵽��Span������pageCache�ϲ�����Span
			// ��ϣ����ӳ��
			// _pageIDToSpan[RemainSpan->_pageID] = RemainSpan;
			// _pageIDToSpan[RemainSpan->_pageID + RemainSpan->_pageNum - 1] = RemainSpan;
			// ����������ӳ��
			_pageIDToSpan.set(RemainSpan->_pageID, RemainSpan);
			_pageIDToSpan.set(RemainSpan->_pageID + RemainSpan->_pageNum - 1, RemainSpan);


			// ȡ��������ҳ��Ҫ����ӳ�䣬�ͷ�ʱ�����ҵ���ӦSpan
			for (int i = 0; i < splitSpan->_pageNum; i++) {
				// ��ϣ����ӳ��
				//_pageIDToSpan[splitSpan->_pageID + i] = splitSpan;
				// ����������ӳ��
				_pageIDToSpan.set(splitSpan->_pageID + i, splitSpan);
			}
			// �ҵ�CentralCache��ʾ��ǰSpan��ʹ��

			// ���ԣ��� RemainSpan �� splitSpan �����ɺ���Ӽ��ʹ�ӡ��
			/*if (RemainSpan->_pageNum + splitSpan->_pageNum != i) {
				printf("Debug: PageCache split error! RemainSpan pageNum: %zu, splitSpan pageNum: %zu\n",
					RemainSpan->_pageNum, splitSpan->_pageNum);
			}*/
			// ���ԣ�ȷ�� splitSpan �� RemainSpan ��ҳ�ŷ�Χ��ȷӳ�䡣
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
	// �Ӷѿռ������µ��ڴ�
	void* newMemory = Utils::SystemAllocate(MAX_PAGE - 1);

	// ���ԣ�ȷ��ϵͳ�����ڴ�Ĵ�С����ʼ��ַ��ȷ
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

	// �ϲ����
	// �黹Span��ǰһ��Span�Ƿ���PageCache��
	while (1) {
		//auto prev = _pageIDToSpan.find(returnSpan->_pageID - 1);
		//// û�ҵ��������ϲ�
		//if (prev == _pageIDToSpan.end()) {
		//	break;
		//}
		//SpanNode* prevSpan = prev->second;
		SpanNode* prevSpan = (SpanNode*)_pageIDToSpan.find(returnSpan->_pageID - 1);
		if (prevSpan == nullptr) {
			break;
		}

		// �����span��ʹ�ã������ϲ�
		if (prevSpan->_isUse == true) {
			break;
		}
		// �������Page���ƣ������ϲ�
		if (prevSpan->_pageNum + returnSpan->_pageNum > MAX_PAGE) {
			break;
		}
		_pageCache[prevSpan->_pageNum].Erase(prevSpan);
		returnSpan->_pageID = prevSpan->_pageID;
		returnSpan->_pageNum += prevSpan->_pageNum;
		_spanNodePool.Delete(prevSpan);
	}
	while (1) {
		// ��ϣ����ӳ��
		//auto next = _pageIDToSpan.find(returnSpan->_pageID + returnSpan->_pageNum);
		//// û�ҵ��������ϲ�
		//if (next == _pageIDToSpan.end()) {
		//	break;
		//}
		//SpanNode* nextSpan = next->second;
		// ����������ӳ��
		SpanNode* nextSpan = (SpanNode*)_pageIDToSpan.find(returnSpan->_pageID + returnSpan->_pageNum);
		if (nextSpan == nullptr) {
			break;
		}
	
		// �����span��ʹ�ã������ϲ�
		if (nextSpan->_isUse == true) {
			break;
		}
		// �������Page���ƣ������ϲ�
		if (nextSpan->_pageNum + returnSpan->_pageNum > MAX_PAGE) {
			break;
		}
		_pageCache[nextSpan->_pageNum].Erase(nextSpan);
		returnSpan->_pageNum += nextSpan->_pageNum;
		_spanNodePool.Delete(nextSpan);
	}

	_pageCache[returnSpan->_pageNum].PushFront(returnSpan);
	// �ϲ�����ܸ���Ϊ�Ƿ�ʹ��
	returnSpan->_isUse = false;
	// ��ϣ����ӳ��
	//_pageIDToSpan[returnSpan->_pageID] = returnSpan;
	//_pageIDToSpan[returnSpan->_pageID + returnSpan->_pageNum - 1] = returnSpan;
	// ����������ӳ��
	_pageIDToSpan.set(returnSpan->_pageID, returnSpan);
	_pageIDToSpan.set(returnSpan->_pageID + returnSpan->_pageNum - 1, returnSpan);
	
} 

// ��ַӳ��Span
SpanNode* PageCache::MapAddressToSpan(void* address) {
	assert(address);
	size_t pageID = (PAGE_ID)address >> PAGE_SHIFT;
	// ��ϣ����ӳ��
	// std::unique_lock<std::mutex> lock(_pageMutex);
	/*auto map = _pageIDToSpan.find(pageID);
	if (map != _pageIDToSpan.end()) {
		return map->second;
	}
	else {
		assert(false);
		return nullptr;
	}*/
	// ����������ӳ��
	SpanNode* mapNode = (SpanNode*)_pageIDToSpan.find(pageID);
	assert(mapNode);
	return mapNode;

}

// ���Դ���
//void PageCache::DebugPrintPageCache2(SpanList& pageCache) {
//	SpanNode* current = pageCache.Begin();
//	while (current != pageCache.End()) {
//		printf("  SpanNode - pageID: %llu, pageNum: %zu, isUse: %d\n",
//			current->_pageID, current->_pageNum, current->_isUse);
//		current = current->_next;
//	}
//	printf("End of PageCache\n");
//}


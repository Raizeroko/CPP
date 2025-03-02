#include "CentralCache.h"
#include "PageCache.h"

// ��̬��Ա�������������������ⶨ��
CentralCache CentralCache::_centralCacheInstance;

// ��ȡһ���ǿյ�span(һ��Span���ܷ��˲�ֹ1��Page)
SpanNode* CentralCache::GetOneSpan(SpanList& spanList, size_t alignSize)
{
	// ���CentralCache[index]���޿ɷ���Span
	SpanNode* spanCur = spanList.Begin();
	while (spanCur != spanList.End()) {
		if (spanCur->_freeList != nullptr) {
			return spanCur;
		}
		spanCur = spanCur->_next;
	}

	// ��PageCache��ȡkҳ���棬��ʱ����Ҫ�����Ļ�������������ͷ����������̲߳������Թ黹�ڴ棬ͬʱҲ�ܽ�������ķ��䡣
 	spanList._mutex.unlock();
	size_t numPage = Utils::NumPage(alignSize);

	// �����ж���߳�ͬʱ��PageCache��ȡ�ڴ�
	PageCache::GetInstance()->_centralMutex.lock();
	// ��PageCache��ȡKҳ���ڴ���Ϣ��ҳ�ţ�ҳ����
	SpanNode* kPage = PageCache::GetInstance()->GetKPage(numPage);
	PageCache::GetInstance()->_centralMutex.unlock();


	// ����ҳ�Ż�ȡ������ڴ��ַ,��char*��������alignSize�����ָ��ַ
	kPage->_freeList = (void*)(kPage->_pageID << PAGE_SHIFT);
	char* cur = (char*)kPage->_freeList;
	size_t bytes = numPage << PAGE_SHIFT;
	char* end = cur + bytes;
	char* next = cur + alignSize;
	// ����PageCache������ڴ�
	while (cur < end - alignSize) {
		FreeList::Next(cur) = next;
		cur = next;
		next = next + alignSize;
	}
	// cur = end - alignSize, ������βָ��
	FreeList::Next(cur) = nullptr;

	// Ҫ�����Ļ�����������Լ���
	spanList._mutex.lock();

	// �����Ӻõ��ڴ�������Ļ�����
	spanList.PushFront(kPage);
	return kPage;
}

// �����Ļ����ȡһ�������Ķ����thread cache
size_t CentralCache::FetchToThreadCache(void*& start, void*& end, size_t batchSize, size_t alignSize)
{
	size_t index = Utils::Index(alignSize);

	// ��ͬ�߳̿���ͬʱ�����Ļ���ͬһ��SpanList���ʣ�������Ҫ����
	_centralCache[index]._mutex.lock();

	// ��alignSize
	SpanNode* spanHead = GetOneSpan(_centralCache[index], alignSize);
	assert(spanHead);
	assert(spanHead->_freeList);
	start = spanHead->_freeList;
	end = start;
	size_t actualSize = 1;

	// �ָ�
	while (FreeList::Next(end) != nullptr && actualSize < batchSize) {
		actualSize++;
		end = FreeList::Next(end);
	}
	spanHead->_freeList = FreeList::Next(end);
	FreeList::Next(end) = nullptr;
	spanHead->_useCount += actualSize;
	_centralCache[index]._mutex.unlock();

	return actualSize;
}


void CentralCache::ReturnFromThreadCache(void* start, size_t alignSize) {
	// ��ThreadCache���ص��������һ�CentralCache
	size_t index = Utils::Index(alignSize);

	// �黹����һ��Span��
	SpanNode* returnSpan = PageCache::GetInstance()->MapAddressToSpan(start);

	// Ҫ��CentralCache��������Ҫ����
	_centralCache[index]._mutex.lock();

	while (start) {
		// ͷ�嵽��span��freeList;
		void* next = FreeList::Next(start);
		FreeList::Next(start) = returnSpan->_freeList;
		returnSpan->_freeList;
		returnSpan->_useCount--;
		if (returnSpan->_useCount == 0) {
			// ��CentralCache�����span

			/*
			_centralCache->Erase(returnSpan); ����д��Ϊʲô���ᱨ����������
			�������˻�Ϊָ�룺��ʹ�� _centralCache-> ʱ�������� _centralCache ����ʽ�˻�Ϊָ��������Ԫ�ص�ָ��
			(&_centralCache[0])->Erase(returnSpan);
			*/ 

			_centralCache[index].Erase(returnSpan);  
			// PageCache��ͨ��_pageID�ҵ���ַ������Ҫ����_freeList�����ӣ�����ֱ��ָ��
			returnSpan->_freeList == nullptr;

			// �黹��PageCache��ʾû�б�ʹ��
			returnSpan->_isUse = false;

			// �黹��PageCache���CentralCache����������PageCache����
			_centralCache[index]._mutex.unlock();
			PageCache::GetInstance()->_centralMutex.lock();
			PageCache::GetInstance()->ReturnFromCentralCache(returnSpan);
			// �ص�CentralCache���PageCache����������CentralChe����
			PageCache::GetInstance()->_centralMutex.unlock();
			_centralCache[index]._mutex.lock();
		}
		start = next;
	}
	_centralCache[index]._mutex.unlock();


}


//void CentralCache::ReturnFromCentralCache(void* start, size_t alignSize) {
//	// ��ThreadCache���ص��������һ�CentralCache
//	size_t index = Utils::Index(alignSize);
//
//	while (start) {
//
//		void* next = Next(start);
//
//		// �����ĸ�span??
//		SpanNode* span = new SpanNode;
//		FreeList::Next(start) = span->_freeList;
//		span->_freeList = start;
//		span->_useCount--;
//		
//		// ��span����Ѿ�ȫ���һأ���CentralCache�黹��ThreadCache
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


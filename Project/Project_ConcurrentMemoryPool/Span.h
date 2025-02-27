#pragma once
#include "FreeList.h"
#include <cassert>
#include <mutex>


#ifdef _WIN64
typedef unsigned long long PAGE_ID;
#elif _WIN32
typedef size_t PAGE_ID;
#endif

struct SpanNode {
	// ҳ��
	PAGE_ID _pageID = 0;
	// ����ҳ������
	size_t _n = 0;


	//˫��ѭ������
	SpanNode* _prev = nullptr;
	SpanNode* _next = nullptr;

	//ÿ��SpanNode�¹ҵĴ�ҳ����ָ�õ�����
	void* _freeList = nullptr;

	// ��Page�Ѿ�ʹ�õ��ڴ���
	size_t _usecount = 0;
};


// ��ͷ˫������
class SpanList {
	SpanList() {
		// ��ʼ����ͷ˫��ѭ��������ǰ��ָ��ָ��ͷ
		_spanListHead = new SpanNode();
		_spanListHead->_next = _spanListHead;
		_spanListHead->_prev = _spanListHead;
	}
	void Insert(SpanNode* pos, SpanNode* pushNode) {
		assert(pos);
		assert(pushNode);

		SpanNode* prev = pos->_prev;
		prev->_next = pushNode;
		pushNode->_prev = prev;

		pushNode->_next = pos;
		pos->_prev = pushNode;
	}

	void Erase(SpanNode* pos) {
		assert(pos);
		assert(pos != _spanListHead);
		SpanNode* prev = pos->_prev;
		SpanNode* next = pos->_next;
		prev->_next = next;
		next->_prev = prev;
		pos->_prev = nullptr;
		pos->_next = nullptr;
	}

public:
	SpanNode* _spanListHead = nullptr;
	std::mutex _mutex;

};

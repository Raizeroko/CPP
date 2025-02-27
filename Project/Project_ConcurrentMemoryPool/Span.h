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
	// 页号
	PAGE_ID _pageID = 0;
	// ？？页的数量
	size_t _n = 0;


	//双向循环链表
	SpanNode* _prev = nullptr;
	SpanNode* _next = nullptr;

	//每个SpanNode下挂的从页缓存分割好的链表
	void* _freeList = nullptr;

	// 该Page已经使用的内存数
	size_t _usecount = 0;
};


// 带头双向链表
class SpanList {
	SpanList() {
		// 初始化带头双向循环链表，将前后指针指向头
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

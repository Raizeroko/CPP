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
	// 页数量
	size_t _pageNum = 0;

	// 该Span是否在用
	bool _isUse = false;

	//双向循环链表
	SpanNode* _prev = nullptr;
	SpanNode* _next = nullptr;

	//每个SpanNode下挂的从页缓存分割好的链表
	void* _freeList = nullptr;

	// 该Page已经使用的内存数
	size_t _useCount = 0;
};


// 带头双向链表
class SpanList {
public:
	SpanList() {
		// 初始化带头双向循环链表，将前后指针指向头
		_spanListHead = new SpanNode();
		_spanListHead->_next = _spanListHead;
		_spanListHead->_prev = _spanListHead;
	}

	SpanNode* Begin() {
		return _spanListHead->_next;
	}

	SpanNode* End() {
		return _spanListHead;
	}

	bool Empty() {
		return _spanListHead == _spanListHead->_next;
	}

	SpanNode* PopFront() {
		SpanNode* popNode = Begin();
		Erase(popNode);
		return popNode;

	}

	void PushFront(SpanNode* pushNode) {
		Insert(End(), pushNode);
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

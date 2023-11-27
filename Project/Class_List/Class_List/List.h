#pragma once

#include<iostream>

namespace zwr {
	template<class T>
	struct list_node {

		list_node(const T& val = T())
			: _val(val)
			, _prev(nullptr)
			, _next(nullptr)
		{}

		T _val;
		list_node<T>* _prev;
		list_node<T>* _next;
	};
	
	template<class T>
	class list {
		typedef list_node<T> node;
	public:
		list()
		{
			_head = new node;
			_node->_next = _head;
			_node->_prev = _head;
		}

		

	private:
		node* _head;
	};
}

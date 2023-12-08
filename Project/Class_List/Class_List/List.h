#pragma once

#include<iostream>
#include<algorithm>

namespace zwr {
	template<class T>
	struct list_iterator {
		typedef list_node<T> node;
		typedef list_iterator<T> iterator;

		node* _node;

		list_iterator(node* p)
			:_node(p)
		{}

		T opeartor* ()
		{
			return _node->_val;
		}

		T& operator++()
		{
			_node=_node->_next;
			return *this;
		}
		T& operator++(int)
		{
			iterator tmp = _node;
			_node=_node->next;
			return tmp;
		}
		operator!=(iterator x)
		{
			return _node != x._node;
		}

	};


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
		typedef list_iterator<T> iterator;
		typedef list_node<T> node;
	public:
		

		//Constructor
		list()
		{
			_head = new node;
			_head->_next = _head;
			_head->_prev = _head;
		}
		list(const list& x)
		{
			//
		}

		//Iterator
		iterator begin()
		{
			return iterator(_head->next);
		}
		iterator end()
		{
			return iterator(_head);
		}

		//Capacity
		bool empty()
		{
			return _head->_next == _head->_prev;
		}
		size_t size()
		{
			//
		}

		//Access
		T& front()
		{
			if (!empty())
			{
				return _head->_next->_val;
			}
		}
		T& back()
		{
			if (!empty())
			{
				return _head->_prev->_val;
			}
		}


		//Modifiers
		void push_back(const T& val)
		{
			node* tmp = new node(val);
			node* tail = _head->_prev;

			_head->_prev = tmp;
			tmp->_next = _head;
			tail->_next = tmp;
			tmp->_prev = tail;
		}
		void pop_back()
		{
			if (empty)
				return;

			node* tail = _head->_prev;
			node* new_tail = tail->_prev;
			new_tail->_next = _head;
			_head->_prev = new_tail;

			delete tail;
		}
		void push_front(const T& val)
		{
			node* tmp = new node(val);
			node* front = _head->_next;

			_head->_next = tmp;
			tmp->_prev = _head;
			front->prev = tmp;
			tmp->_next = front;
		}
		void pop_front()
		{
			if (empty)
				return;

			node* front = _head->_next;
			node* new_front = front->_next;
			_head->_next = new_front;
			new_front->_prev = _head;

			delete front;
		}
		void swap(list<T>& x)
		{
			swap(_head, x);
		}

	
		

	private:
		node* _head;
	};
}

#pragma once

#include<iostream>
#include<algorithm>
#include<assert.h>
using namespace::std;

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

	/*template<class T>
	struct list_const_iterator {
		typedef list_node<T> node;
		typedef list_const_iterator<T> self;

		node* _node;

		list_const_iterator(node* p)
			:_node(p)
		{}

		const T& operator *()
		{
			return _node->_val;
		}
		self operator++ ()
		{
			_node = _node->_next;
			return _node;
		}
		self operator-- ()
		{
			_node = _node->_prev;
			return _node;
		}
		self operator++(int)
		{
			self tmp = _node;
			_node = _node->_next;
			return tmp;
		}
		self operator-- (int)
		{
			_node = _node->_prev;
			return _node;
		}
		bool operator!=(self x)
		{
			return _node != x._node;
		}
		bool operator==(self x)
		{
			return _node == x._node;
		}
	};*/


	template<class T, class Ref, class Ptr>
	struct list_iterator {
		typedef list_node<T> node;
		typedef list_iterator<T, Ref, Ptr> self;

		node* _node;

		list_iterator(node* p)
			:_node(p)
		{}
		Ref operator *()
		{
			return _node->_val;
		}
		/*const T& operator *() const
		{
			return _node->_val;
		}*/

		/*const iterator operator++ () const
		{
			_node = _node->_next;
			return _node;
		}*/
		self operator++ ()
		{
			_node=_node->_next;
			return _node;
		}
		self operator-- ()
		{
			_node = _node->_prev;
			return _node;
		}
		self operator++(int)
		{
			self tmp = _node;
			_node=_node->_next;
			return tmp;
		}
		self operator-- (int)
		{
			_node = _node->_prev;
			return _node;
		}
		bool operator!=(self x)
		{
			return _node != x._node;
		}
		bool operator==(self x)
		{
			return _node == x._node;
		}
		/*bool operator!=(iterator x)	const
		{
			return _node != x._node;
		}*/
		Ptr operator ->()
		{
			return &(_node->_val);
		}

		/*const T* operator->() const
		{
			return &(_node->_val);
		}*/
	};


	
	
	template<class T>
	class list {
	public:
		typedef list_node<T> node;

		typedef list_iterator<T, T&, T*> iterator;
		typedef list_iterator<T, const T&, const T*> const_iterator;
		/*typedef const list_iterator<T> const_iterator;*/


		//Constructor
		void empty_init()
		{
			_head = new node;
			_head->_next = _head;
			_head->_prev = _head;
		}
		list()
		{
			empty_init();
		}
		template<class InputIterator>
		list(InputIterator first, InputIterator last)
		{
			empty_init();
			while (first != last)
			{
				push_back(*first);
				first++;
			}
		}
		list(const list<T>& x)
		{
			empty_init();
			list<T> tmp(x.begin(), x.end());
			swap(tmp);
		}
		list<T>& operator=(list<T> x)
		{
			swap(x);
			return *this;
		}
		~list()
		{
			while (!empty())
			{
				pop_back();
			}
			delete _head;
			_head = nullptr;
		}

		//Iterator
		iterator begin()
		{
			return iterator(_head->_next);
		}

		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}

		const_iterator end() const
		{
			return const_iterator(_head);
		}


		//Capacity
		bool empty()
		{
			return _head == _head->_prev;
		}
		size_t size()	
		{
			size_t ret = 0;
			auto it = begin();
			while (it++ != end())
			{
				ret++;
			}
			return ret;
		}

		//Access
		T& front()
		{
			assert(!empty());
			return _head->_next->_val;
		}

		T& back()
		{
			assert(!empty());
			return _head->_prev->_val;
		}


		//Modifiers
		iterator insert(iterator pos, const T& val)
		{
			node* cur = pos._node;
			node* prev = cur->_prev;
			node* new_node = new node(val);

			prev->_next = new_node;
			new_node->_prev = prev;
			cur->_prev = new_node;
			new_node->_next = cur;

			return iterator(new_node);
		}
		iterator erase(iterator pos)
		{
			assert(!empty());
			node* cur = pos._node;
			node* prev = cur->_prev;
			node* next = cur->_next;

			next->_prev = prev;
			prev->_next = next;
			delete cur;
			return iterator(next);
		}
		
		void push_back(const T& val)
		{
			/*node* tmp = new node(val);
			node* tail = _head->_prev;

			_head->_prev = tmp;
			tmp->_next = _head;
			tail->_next = tmp;
			tmp->_prev = tail;*/
			insert(end(), val);

		}
		void pop_back()
		{
			/*if (empty)
				return;

			node* tail = _head->_prev;
			node* new_tail = tail->_prev;
			new_tail->_next = _head;
			_head->_prev = new_tail;

			delete tail;*/
			erase(--end());
		}
		void push_front(const T& val)
		{
			/*node* tmp = new node(val);
			node* front = _head->_next;

			_head->_next = tmp;
			tmp->_prev = _head;
			front->prev = tmp;
			tmp->_next = front;*/
			insert(begin(), val);
		}
		void pop_front()
		{
			/*if (empty)
				return;

			node* front = _head->_next;
			node* new_front = front->_next;
			_head->_next = new_front;
			new_front->_prev = _head;

			delete front;*/
			erase(begin());
		}
		void swap(list<T>& x)
		{
			std::swap(_head, x._head);
		}
		void clear()
		{
			while (!empty())
			{
				pop_back();
			}
		}

	private:
		node* _head;
	};
}

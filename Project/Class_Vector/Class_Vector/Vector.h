#pragma once
#include<iostream>
#include<assert.h>

namespace zwr {
	template<class T>
	class vector {
	public:

		typedef T* iterator;
		typedef const T* const_iterator;

		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator begin() const
		{
			return _start;
		}
		const_iterator end() const
		{
			return _finish;
		}
		//constructor
		vector()
		{}
		vector(size_t n, const T& val = T())
		{
			_start = new T[n];
			
			T* tmp = _start;
			while (tmp != _start + n)
			{
				*tmp = val;
				tmp++;
			}
			_finish = _start + n;
			_endofstorage = _start + n;
		}
		vector(const vector& v)
		{
			_start = new T[v.capacity()];
			for (int i = 0; i < v.size(); i++)
			{
				_start[i] = v._start[i];
			}
			_finish = _start + v.size();
			_endofstorage = _start + v.capacity();
		}
		template<class InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			size_t sz = last - first;
			reserve(sz);
			T* tmp = _start;
			for (int i = 0; i < sz; i++)
			{
				tmp[i] = first[i];
			}
			_finish = _start + sz;
		}
		/*T& operator=(const T& x)
		{
			T* tmp = T(x);
			swap(tmp);
			
			return *this;
		}*/
		

		//capacity
		size_t size() const
		{
			return _finish - _start;
		}
		size_t capacity() const
		{
			return _endofstorage - _start;
		}

		void resize(size_t n, T val = T())
		{
			if (n < size())
			{
				_finish = _start + n;
			}
			else 
			{
				if (n > capacity())
					reserve(n);
				while (_finish != _start + n)
				{
					*_finish = val;
					_finish++;
				}
			}
			
		}
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				T* tmp = new T[n];
				size_t sz = size();
				if (_start)
				{
					for (size_t i = 0; i < sz; i++)
					{
						tmp[i] = _start[i];
					}
					delete[] _start;
				}
				_start = tmp;
				_finish = tmp + sz;
				_endofstorage = tmp + n;
			}
		}
		bool empty() const
		{
			if (_finish == _start)
			{
				return true;
			}
			return false;
		}
		//access
		T& operator[](size_t n)
		{
			return _start[n];
		}

		//modifiers
		void push_back(const T& val)
		{
			if (capacity() == size())
			{
				reserve(capacity() == 0 ? 4 : 2 * capacity());
			}
			*_finish = val;
			_finish++;
		}
		void pop_back()
		{
			assert(!empty());
			_finish--;
		}
		iterator insert(iterator pos, const T& val)
		{
			//sz用于处理迭代器失效
			int posi = pos - _start;
			if (_finish == _endofstorage)
			{
				reserve(capacity() == 0 ? 4 : 2 * capacity());
			}
			iterator end = _finish;
			pos = _start + posi;
			while (end != pos)
			{
				*end = *(end - 1);
				end--;
			}
			*pos = val;
			_finish++;
			return end;
		}
		void insert(iterator pos, size_t n, const T& val)
		{
			int posi = pos - _start;
			if (_finish == _endofstorage)
			{
				reserve(capacity() + n);
			}
			iterator end = _finish + n;
			pos = _start + posi;
			while (end != pos + n)
			{
				*(end-1) = *(end - n - 1);
				--end;
			}
			while (pos != end)
			{
				*pos = val;
				pos++;
			}
			_finish += n;
		}
		iterator erase(iterator pos)
		{
			//sz控制迭代器失效
			int sz = pos - _start;
			iterator end = pos+1;
			while (end != _finish)
			{
				*(end-1) = *end;
				end++;
			}
			_finish--;
			//返回删除的pos位置的下一个位置
			return _start + sz;
		}
		iterator erase(iterator first, iterator last)
		{
			int sz = last - first;
			iterator end = last;
			while (end != _finish)
			{
				*(end - sz) = *end;
				end++;
			}
			_finish -= sz;
			return end - sz;
		}
		void swap(vector& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endofstorage, v._endofstorage);
		}
		void clear()
		{
			erase(begin(), end());
		}


		//destructor
		~vector()
		{
			delete[] _start;
			_start = nullptr;
			_finish = nullptr;
			_endofstorage = nullptr;
		}
	private:
		iterator _start = nullptr;
		iterator _finish = nullptr;
		iterator _endofstorage = nullptr;
	};
}


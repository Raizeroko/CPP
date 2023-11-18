#pragma once
#include<iostream>

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




		T& operator[](size_t n)
		{
			return _start[n];
		}
		//capacity
		size_t size() const
		{
			return _finish - _start;
		}
		size_t capacity() const
		{
			return _endofstorage - _start;
		}

		void resize(size_t n)
		{
			if (n > capacity())
			{
				reserve(n);
			}
			_finish = _start + n;
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
		bool empty()
		{
			if (_finish == _start)
			{
				return true;
			}
			return false;
		}



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


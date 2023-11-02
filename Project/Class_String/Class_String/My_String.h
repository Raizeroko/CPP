#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>

	
namespace zwr {
	class String {
	public:
		//constructor
		String()
			:_str(new char[1])
			,_size(0)
			,_capacity(1)
		{
			_str[0] = '\0';
		}
		String(const String& s)
			:_size(s._size)
		{
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str, s._str);
		}
		String(const String& s, size_t pos, size_t len = npos)
		{
			assert((pos <= s._size) || pos >= 0);
			_size = s._size;
			_capacity = _size;
			_str = new char[_capacity + 1];

			if (pos + len > s._size || len == npos)
			{
				strcpy(_str, s._str + pos);
			}
			else
			{
				for (size_t i = 0; i < len; i++)
				{
					*(_str + i) = *(s._str + pos + i);
				}
				*(_str + len) = '\0';
			}
			
		}
		String(const char* s)
			:_size(strlen(s))
		{
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str, s);
		}

		const char* c_str() const
		{
			return _str;
		}

		//capacity
		size_t size()	const
		{
			return _size;
		}
		size_t length()	const
		{
			return _capacity;
		}
		void resize(size_t n)
		{
			if (n <= _size)
			{
				_str[n] = '\0';
				_size = n;
			}
			else
			{
				if (n > _capacity)
				{
					this->reserve(n);
				}
				for (size_t i = _size; i < n; i++)
				{
					_str[i] = ' ';
				}
				_str[n] = '\0';
			}
		}
		void resize(size_t n, char c)
		{
			if (n <= _size)
			{
				_str[n] = '\0';
				_size = n;
			}
			else
			{
				if (n > _capacity)
				{
					this->reserve(n);
				}
				for (size_t i = _size; i < n; i++)
				{
					_str[i] = ' ';
				}
				_str[n] = c;
			}
		}
		void reserve(size_t n = 0)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n+1];
				if (tmp != nullptr)
				{
					strcpy(tmp, _str);
					delete[] _str;
					_str = tmp;
					_capacity = n;
				}
			}
		}

		//destructor
		~String()
		{
			if (_str)
			{
				delete[] _str;
				_str = nullptr;
			}
		}

	private:
		char* _str;
		size_t _size;
		size_t _capacity;
		const static size_t npos = -1;
	};
	//?
	//const static size_t npos = -1;
}
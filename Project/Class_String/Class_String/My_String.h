#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>

	
namespace zwr {
	class String {
	public:
		typedef char* iterator;
		typedef const char* const_iterator;

		//iterator
		iterator begin()
		{
			return _str;
		}
		const_iterator begin() const
		{
			return _str;

		}
		iterator end()
		{
			return _str + _size;
		}
		const_iterator end() const
		{
			return _str + _size;
		}
		char& operator[](size_t pos)
		{
			return _str[pos];
		}
		const char& operator[](size_t pos) const
		{
			return _str[pos];
		}


		//constructor
		String()
			:_str(new char[1])
			,_size(0)
			,_capacity(0)
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
				_size = n;
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
					_str[i] = c;
				}
				_str[n] = '\0';
				_size = n;
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
		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}
		bool empty() const
		{
			if (_size == 0)
				return true;
			return false;
		}
		//modifiers
		void push_back(char c)
		{
			if (_size == _capacity)
			{
				reserve(2 * _size + 1);
			}
			_str[_size] = c;
			_size++;
			_str[_size] = '\0';
		}
		String& append(const char* str)
		{
			size_t len = strlen(str);
			if (len + _size > _capacity)
			{
				reserve(len + _size);
			}
			strcpy(_str + _size, str);
			return *this;
		}
		String& operator+= (const String& str)
		{
			
			append(str._str);
			return *this;

		}
		String& operator+= (const char* str)
		{
			append(str);
			return *this;
		}
		String& operator+= (char c)
		{
			push_back(c);
			return *this;
		}
		String& assign(const String& str)
		{
			if (_capacity < str._size)
			{
				reserve(str._size);
			}
			strcpy(_str, str._str);
			return *this;
		}
		String& assign(const char* s)
		{
			size_t len = strlen(s);
			if (_capacity < len)
			{
				reserve(len);
			}
			strcpy(_str, s);
			return *this;
		}
		String& insert(size_t pos, const char* s)
		{
			assert(pos < _size && pos >= 0);
			size_t len = strlen(s);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			size_t end = _size;
			while (end >= pos)
			{
				_str[end + len] = _str[end];
				end--;
			}
			for (size_t i = 0; i < len; i++)
			{
				_str[pos + i] = s[i];
			}
			_size += len;
			return *this;
		}
		String& insert(size_t pos, const String& str)
		{
			insert(pos, str._str);
			return *this;
		}
		String& erase(size_t pos = 0, size_t len = npos)
		{
			assert(pos <= _size);
			if (pos + len > _size || len == npos)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				size_t end = pos+len;
				while (end <= _size)
				{
					_str[end - len] = _str[end];
					end++;
				}
				_size -= len;
			}
		}
		void pop_back()
		{
			_str[_size - 1] = '\0';
			_size--;
		}
		//overloads
		bool operator<(const String& s) const
		{
			int ret = strcmp(_str, s._str);
			return ret < 0 ? true : false;
		}
		bool operator==(const String& s) const
		{
			int ret = strcmp(_str, s._str);
			return ret == 0 ? true : false;
		}
		bool operator>(const String& s) const
		{
			return !(*this <= s);
		}
		bool operator>=(const String& s) const
		{
			return !(*this < s);
		}
		bool operator<=(const String& s) const
		{
			return (*this < s || *this == s);
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
	public:
		const static size_t npos;
	};
	//?
	const size_t String::npos = -1;


	std::ostream& operator<<(std::ostream& os, const String& s)
	{
		for (int i = 0; i < s.size(); i++)
		{
			os << s[i];
		}
	}


	//不是自己写的
	std::istream& operator>>(std::istream& is, String& s)
	{
		s.clear();
		char ch = is.get();
		while (ch == ' ' || ch == '\n')
		{
			ch = is.get();
		}
		char buff[128];
		int i = 0;

		while (ch != ' ' && ch != '\n')
		{
			buff[i++] = ch;
			if (i == 127)
			{
				buff[i] = '\0';
				s += buff;
				i = 0;
			}

			//in >> ch;
			ch = is.get();
		}

		if (i != 0)
		{
			buff[i] = '\0';
			s += buff;
		}

		return is;

	}
}



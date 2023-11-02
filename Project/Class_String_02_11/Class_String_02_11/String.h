#pragma once

#include<assert.h>
#include<iostream>
//#include<string.h>
//#include<new>

using namespace std;

namespace zwr
{
	class string
	{
	public:
		//迭代器类型命名
		typedef char* iterator;
		typedef const char* const_iterator;
		/////
		//c_str
		char* c_str()
		{
			return _str;
		}
		//operator[]
		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}
		//const operator[]
		const char& operator[](size_t pos) const
		{
			assert(pos < _size);
			return _str[pos];
		}
		/////string构造相关函数
		//构造函数
		string(const char* str = "")
			:_str(new char[strlen(str) + 1])
			,_size(strlen(str))
			,_capacity(_size)

		{
			strcpy(_str, str);
		}
		//拷贝函数
		string(const string& s)
			:_str(new char[strlen(s._str) + 1])
			, _size(s._size)
			, _capacity(_size)
		{

			strcpy(_str, s._str);
		}
		//等号拷贝
		string& operator=(const string& s)
		{
			*this = s._str;
			return *this;
		}
		//等号构造
		string& operator=(const char* str)
		{
			_str = new char[strlen(str) + 1];
			_size = strlen(str);
			_capacity = _size;
			strcpy(_str, str);
			return *this;
		}
		//析构函数
		~string()
		{
			delete[] _str;
			_size = 0;
			_capacity = 0;
			reserve(0);
		}
		/////string迭代器相关函数
		//begin
		iterator begin()
		{
			return _str;
		}
		//end
		iterator end()
		{
			return _str + _size;
		}
		//const begin
		const_iterator begin() const
		{
			return _str;
		}
		//const end
		const_iterator end() const
		{
			return _str + _size;
		}
		/////string容量相关函数
		//size
		size_t size() const
		{
			return _size;
		}
		//capacity
		size_t capacity() const
		{
			return _capacity;
		}
		//reserve
		void reserve(size_t new_capacity = 0)
		{
			if (new_capacity > _capacity)
			{
				char* tmp = new char[new_capacity + 1];
				strcpy(tmp, _str);
				delete[] _str;
				_str = tmp;
				_capacity = new_capacity;
			}
		}
		//resize
		/*void resize(size_t new_size)
		{
			if (new_size < _size)
			{
				_str[new_size] = '\0';
				_size = new_size;
			}
			else
			{
				if (new_size > _capacity)
				{
					reserve(new_size);
				}
				for (int i = _size; i < new_size; i++)
				{
					_str[i] = '\0';
				}
			}
		}*/
		void resize(size_t new_size, char ch = '\0')
		{
			if(new_size > _size)
			{
				if (new_size > _capacity)
				{
					reserve(new_size);
				}
				for (size_t i = _size; i < new_size; i++)
				{
					_str[i] = ch;
				}
			}
			_size = new_size;
			_str[_size] = '\0';
		}
		//clear
		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}
		/////String修改相关函数
		//+=
		string& operator+=(const char* str)
		{
			size_t len = strlen(str);
			if (len + _size > _capacity)
			{
				reserve(len + _size);
			}
			strcpy(_str + _size, str);
			return *this;
		}
		string& operator+=(const string& s)
		{
			*this += s._str;
			return *this;
		}
		string& operator+=(const char ch)
		{
			if (_size == _capacity)
			{
				size_t new_capacity = _size == 0 ? 4 : 2 * _size;
				reserve(new_capacity);
			}
			_str[_size] = ch;
			_size++;
			_str[_size] = '\0';
		}
		//append
		string& append(const string& s)
		{
			*this += s;
			return *this;
		}
		string& append(const char* str)
		{
			*this += str;
			return *this;
		}
		string& append(const string& str, size_t subpos, size_t sublen)
		{
			for (size_t i = subpos; i < subpos + sublen; i++)
			{
				*this += str[i];
			}
			return *this;
		}
		//insert
		string& insert(size_t pos, const char* str)
		{
			assert(pos <= _size);
			size_t len = strlen(str);
			if (len == 0)
			{
				return *this;
			}
			if (len + _size > _capacity)
			{
				reserve(len + _size);
			}
			for (size_t end = pos + len; end >= pos + len; end--)
			{
				_str[end] = _str[end - len];
			}
			for (size_t i = 0; i <= len; i++)
			{
				_str[i + pos] = str[i];
			}
			_size += len;
			return *this;
		}
		string& insert(size_t pos, const string& s)
		{
			return insert(pos, s._str);
		}
		//erase
		string& erase(size_t pos = 0, size_t len = npos)
		{
			assert(pos <= _size);
			if (len == npos || pos + len > _size)
			{
				_str[pos] = '\0';
			}
			else
			{
				strcpy(_str + pos, _str + pos + len);
				_size -= len;
			}
			return *this;

		}
		//swap
		void swap(string& s)
		{
			::swap(_str, s._str);
			::swap(_size, s._size);
			::swap(_capacity, s._capacity);
		}
		//pop_back
		void pop_back()
		{
			_str[_size] = '\0';
			_size--;
		}
		//push_back
		void push_back(const char ch)
		{
			_str += ch;
		}


	private:
		char* _str;
		size_t _size;
		size_t _capacity;
		static const int npos = -1;
	};
	/////
	//string构造相关函数测试
	void StringTest1()
	{
		string s1;
		string s2("hello world");
		string s3(s2);
		string s4 = "hello world";
		string s5 = s4;
	}
	//string迭代器相关函数测试
	void StringTest2()
	{
		string s1 = "1234567";
		const string s2("hello world");
		string::iterator it = s1.begin();
		while (it != s1.end())
		{
			(*it)++;
			cout << *it << ' ';
			it++;
		}
		cout << endl;
		string::const_iterator cit = s2.begin(); 
		while (cit != s2.end())
		{
			cout << *cit << ' ';
			cit++;
		}
		cout << endl;
		for (auto e : s1)
		{
			cout << e << ' ';
		}
		cout << endl;
	}
	//string容量相关函数测试
	void StringTest3()
	{
		string s1("hello world");
		cout << s1.size() << ' ' << s1.capacity()<< endl;
		s1.reserve(5);
		cout << s1.c_str() << endl;
		cout << s1.size() << ' ' << s1.capacity() << endl;
		s1.reserve(15);
		cout << s1.c_str() << endl;
		cout << s1.size() << ' ' << s1.capacity()<< endl;
		s1.resize(5);
		cout << s1.c_str() << endl;
		cout << s1.size() << ' ' << s1.capacity() << endl;
		s1.resize(12,'x');
		cout << s1.c_str() << endl;
		cout << s1.size() << ' ' << s1.capacity() << endl;
		s1.resize(20);
		cout << s1.c_str() << endl;
		cout << s1.size() << ' ' << s1.capacity() << endl;
		s1.clear();
		cout << s1.c_str() << endl;
	}
	//
	void StringTest4()
	{
		;
	}
}
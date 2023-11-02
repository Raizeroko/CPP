#pragma once

#include<iostream>
#include<assert.h>

using namespace std;

namespace zwr
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;
		/////
		//迭代器
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}
		const_iterator begin() const 
		{
			return _str;
		}
		const_iterator end() const
		{
			return _str + _size;
		}
        /////
		//构造函数
		string(const char* str = "\0")
			:_size(strlen(str))
			,_capacity(_size)   //capacity不包括'\0'
		{
			_str = new char[strlen(str) + 1];
			strcpy(_str, str);
		}
		/////
		//拷贝构造（传统写法）
		string(const string& s)
			:_size(s._size)
			,_capacity(_size)
		{
			_str = new char[strlen(s._str) + 1];
			strcpy(_str, s._str);
		}
		/////
		//opertator=（传统写法）
		string& operator=(const char* str)
		{
			delete[] _str;
			_str = new char[strlen(str) + 1];
			strcpy(_str, str);
			_size = strlen(str);
			_capacity = _size;
			return *this;
		}
		string& operator=(const string& s)
		{
			if (this != &s)
			{
				delete[] _str;
				_str = new char[strlen(s._str) + 1];
				strcpy(_str, s._str);
				_size = s._size;
				_capacity = _size;
			}
			return *this;
		}
		/////
		////print
		//char* print()
		//{
		//	return _str;
		//}
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
		//swap
		void swap(string s)
		{
			::swap(_str, s._str);
			::swap(_size, s._size);
			::swap(_capacity, s._capacity);
		}
		//operator[]
		char& operator[](int pos)
		{
			assert(pos <= _size);
			return _str[pos];
		}
		//const operator[]
		const char& operator[](int pos) const 
		{
			assert(pos <= _size);
			return _str[pos];
		}
		/////
		//reserve
		void reserve(size_t new_capacity)
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
		void resize(size_t new_size, char ch = '\0')
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
				while (_size != new_size)
				{
					_str[_size++] = ch;
				}
				_str[_size] = '\0';
			}
		}
		//push_back
		void push_back(char ch)
		{
			if (_size == _capacity)
			{
				int new_capacity = (_capacity == 0 ? 4 : 2 * _capacity);
				reserve(new_capacity);
			}
			_str[_size++] = ch;
			_str[_size] = '\0';
		}

		//append
		void append(const char* str)
		{
			int new_size = _size + strlen(str);
			if (new_size > _capacity)
			{
				reserve(new_size);
			}
			strcpy(_str + _size, str);
			_size = new_size;
		}
		//operator+=
		string& operator+=(const string& s)
		{
			append(s._str);
			return *this;
		}
		string& operator+=(const char* s)
		{
			append(s);
			return* this;
		}
		string& operator+=(char ch)
		{
			push_back(ch);
			return*this;
		}
		/////
		//insert
		string& insert(size_t pos, const char ch)
		{
			if (_size == _capacity)
			{
				int new_capacity = (_capacity == 0 ? 4 : 2 * _capacity);
				reserve(new_capacity);
			}
			size_t end = _size + 1;
			while (end >= pos + 1)
			{
				_str[end] = _str[end - 1];
				end--;
			}
			_str[end] = ch;
			_size++;
			return *this;
		}
		string& insert(size_t pos, const char* str)
		{
			int len = strlen(str);
			if (len == 0)
			{
				return *this;
			}
			if (len + _size > _capacity)
			{
				reserve(len + _size);
			}
			size_t end = _size + len;
			while (end >= pos + len)
			{
				_str[end] = _str[end - len];
				end--;
			}
			for (size_t i = 0; i < len; i++)
			{
				_str[pos + i] = str[i];
			}
			_size += len;
			return* this;
		}
		string& insert(size_t pos, const string& s)
		{
			insert(pos, s._str);
			return *this;
		}
		//erase
		string& erase(size_t pos = 0, size_t len = npos)
		{
			assert(pos >= 0);
			if (len == npos || len+pos > _size)
			{
				_str[pos] = '\0';
				return *this;
			}
			else
			{
				size_t cur = pos + len;
				while (cur != _size)
				{
					_str[cur - len] = _str[cur];
					cur++;
				}
			}
		}
		//c_str
		char* c_str() const
		{
			return _str;
		}
		//clear
		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}
		//析构函数
		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = 0;
			_capacity = 0;
		}


	private:
		char* _str;
		size_t _size;
		size_t _capacity;
		static const size_t npos = -1;
	};

	//operator +
	string operator+(const string& s1, const string& s2)
	{
		string tmp(s1);
		tmp += s2;
		return tmp;
	}
	string operator+(const string& s, char ch)
	{
		string tmp(s);
		tmp += ch;
		return tmp;
	}
	string operator+(const string& s, char* str)
	{
		string tmp(s);
		tmp += str;
		return tmp;
	}
	//operator <<
	ostream& operator<<(ostream& out, string& s)
	{
		out << s.c_str();
		return out;
	}
	//operator >>
	istream& operator>>(istream& in, string& s)
	{
		s.clear();
		char ch = in.get();
		while (ch != '\n' && ch != '\0')
		{
			s += ch;
			ch = in.get();
		}
		return in;
	}
	//getline
	istream& getline(istream& in, string& s)
	{
		s.clear();
		char ch = in.get();
		while (ch != '\n')
		{
			s += ch;
			ch = in.get();
		}
		return in;
	}
	//operator>
	bool operator>(const string& s1, const string s2)
	{
		size_t i1 = 0, i2 = 0;
		while (i1 < s1.size() && i2 < s2.size())
		{
			if (s1[i1] > s2[i2])
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		if (i1 == s1.size())
		{
			return false;
		}
		else
		{
			return true;
		}
		i1++;
		i2++;
	}
	//operator==
	bool operator==(const string& s1, const string& s2)
	{
		size_t i1 = 0, i2 = 0;
		while (i1 < s1.size() && i2 < s2.size())
		{
			if (s1[i1] != s2[i2])
			{
				return false;
			}
			i1++;
			i2++;
		}
		if (i1 == s1.size() && i2 == s2.size())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//opertator>=
	bool operator>=(const string& s1, const string& s2)
	{
		if (s1 > s2 || s1 == s2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//operator<
	bool operator<(const string& s1, const string& s2)
	{
		return !(s1 >= s2);
	}
	//operator<=
	bool operator<=(const string& s1, const string& s2)
	{
		return !(s1 > s2);
	}
	//operator!=
	bool operator!=(const string& s1, const string& s2)
	{
		return !(s1 == s2);
	}
	/////
	///Class_String_Test
	//Class_String成员函数测试
	void StringTest1()
	{
		string s1("hello world");
		cout << s1.c_str() << endl;
		string s2(s1);
		cout << s2.c_str() << endl;
		string s3 = "hello";
		cout << s3.c_str() << endl;
		s3 = s1;
		cout << s3.c_str() << endl;
	}
	//Class_String size函数测试
	void StringTest2()
	{
		string s1("hello world");
		cout << s1.size()<< endl;
		cout << s1.capacity() << endl << endl;
		string s2 = "xxxxxxxxxx";
		swap(s1, s2);
		cout << s1.c_str() << endl;
		cout << s2.c_str() << endl;
		string::iterator it = s1.begin();
		while (it != s1.end())
		{
			cout << *it << ' ';
			it++;
		}
		cout << endl;
		s1.resize(3);
		cout << s1.size() << ' ' << s1.capacity() << endl;
		s1.resize(7);
		cout << s1.size() << ' ' << s1.capacity() << endl;
		s1.resize(20);
		cout << s1.size() << ' ' << s1.capacity() << endl;
		s2.reserve(3);
		cout << s2.size() << ' ' << s2.capacity() << endl;
		s2.reserve(7);
		cout << s2.size() << ' ' << s2.capacity() << endl;
		s2.reserve(20);
		cout << s2.size() << ' ' << s2.capacity() << endl;
	}
	//Class_String增，删，改函数
	void StringTest3()
	{
		string s1 = "hello world";
		string s2 = "1234567";
		string s3 = "ss";
		cout << s1 << endl;
		s1.push_back('!');
		cout << s1 << endl;
		s1.append("xxxx");
		cout << s1 << endl;
		s1 += '1';
		cout << s1 << endl;
		s1 += "22";
		cout << s1 << endl;
		s1 += s2;
		cout << s1 << endl << endl;
		cout << s2 << endl;
		s2.insert(0, s3);
		cout << s2 << endl;
		s2.insert(2, "!!!");
		cout << s2 << endl;
		s2.erase(2, 3);
		cout << s2 << endl;
		s2.erase();
		cout << s2 << endl;

	}
	//Class_String输入输出流运算符
	void StringTest4()
	{
		string s1("hello world");
		cout << s1 << endl;
		cin >> s1;
		cout << s1 << endl;

	}
	//Class_String bool运算符
	void StringTest5()
	{
		string s1("hello world");
		string s2(s1);
		if (s1 == s2)
		{
			cout << "s1 == s2" << endl;
		}
		s2 += 'x';
		if (s1 > s2)
		{
			cout << "s1 > s2" << endl;
		}
		if (s1 < s2)
		{
			cout << "s1 < s2" << endl;
		}
		s1 += 'x';
		cout << s1 << endl;
		cout << s2 << endl;
		if (s1 >= s2)
		{
				cout << "s1 >= s2" << endl;
		}
		if (s1 <= s2)
		{
			cout << "s1 <= s2" << endl;
		}

	}


	//class Data
	//{
	//public:
	//	Data(int year = 1, int month = 1, int day = 1)
	//		:_year(year)
	//		,_month(month)
	//		,_day(day)
	//	{}

	//	void shownpos() const
	//	{
	//		if (_year != npos)
	//		{
	//			cout << "npos != 1" << endl;
	//		}
	//	}
	//	
	//private:
	//	int _year;
	//	int _month;
	//	int _day;
	//	static const int npos = -1;
	//};
	////const int Data::npos = -1;

	//void StaticTest()
	//{
	//	Data a(-1);
	//	a.shownpos();
	//	
	//}
}

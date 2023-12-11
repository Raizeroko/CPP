#pragma once

#include<iostream>
#include<vector>
using namespace std;

namespace zwr{
	template<class T, class Container=vector<T>>
	class stack {
	public:
		stack(const Container& con = Container())
			:_con(con)
		{}

		bool empty()
		{
			return _con.empty();
		}
		size_t size()
		{
			return _con.size();
		}

		T& top()
		{
			return _con[size() - 1];
		}

		void push(const T& val)
		{
			_con.push_back(val);
		}

		void pop()
		{
			_con.pop_back();
		}

	private:
		Container _con;
	};
}
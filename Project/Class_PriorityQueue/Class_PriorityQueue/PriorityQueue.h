#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

namespace zwr {
	template<class T>
	class Less {
	public:
		bool operator()(const T& a,const T& b)
		{
			return a < b;
		}
	};

	template<class T>
	class Greater {
	public:
		bool operator()(const T& a, const T& b)
		{
			return a > b;
		}
	};

	template<class T, class Container = vector<T>, class Compare = Less<T>>
	class priority_queue {
	private:
		void AdjustUp()
		{
			//Compare compare;
			int n = _con.size() - 1;
			while (n)
			{
				int m = (n - 1) / 2;
				if (Compare()(_con[m],_con[n]))
				{
					swap(_con[n], _con[m]);
					n = m;
				}
				else
				{
					break;
				}

			}
		}
		void AdjustDown()
		{
			if (!_con.empty())
			{
				int n = 0;
				while ((n*2+1) < _con.size())
				{
					int m = n * 2 + 1;
					if (m + 1 < _con.size() && Compare()(_con[m],_con[m + 1]))
					{
						m++;
					}
					if (Compare()(_con[n],_con[m]))
					{
						swap(_con[n], _con[m]);
						n = m;
					}
					else
					{
						break;
					}

				}
			}
		}

	public:
		priority_queue()
		{}
		template<class Inputierator>
		priority_queue(Inputierator first, Inputierator last)
		{
			Container tmp(first, last);
			_con.swap(tmp);
		}
		bool empty() const
		{
			return _con.empty();
		}
		size_t size() const
		{
			return _con.size();
		}
		const T& top() const
		{
			return _con[0];
		}
		void push(const T& val)
		{
			_con.push_back(val);
			AdjustUp();
		}
		void pop()
		{
			swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			AdjustDown();
		}

	private:
		Container _con;
	};
}

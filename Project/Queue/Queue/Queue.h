#pragma once
#include<list>


namespace zwr {
	template<class T, class Container = std::list<T>>
	class queue {
	public:
		queue(const Container& con = Container())
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
		T& front()
		{
			return _con.front();
		}
		T& back()
		{
			return _con.back();
		}
		void push(const T& val)
		{
			_con.push_back(val);
		}
		void pop()
		{
			_con.pop_front();
		}
	private:
		Container _con;
	};
}

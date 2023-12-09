#include "List.h"
template<class T>
void print(const zwr::list<T>& l)
{
	auto it = l.begin();
	//zwr::list<int>::const_iterator it = l.begin();
	//it = l.end();
	//cout << *it;
	while (it != l.end())
	{
		cout << it->_year << ' ';
		cout << it->_month <<' ';
		cout << it->_day <<' ';
		cout << endl;
		++it;
	}
	/*for (auto& e : l)
	{
		e++;
		cout << e << ' ';

	}*/
	cout << endl;
}

struct Date {
	Date()
		: _year(2023)
		, _month(12)
		, _day(9)
	{}
	int _year;
	int _month;
	int _day;
};

void test_const_iterator()
{
	zwr::list<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);
	//print(list);

	zwr::list<Date> list_date;
	list_date.push_back(Date());
	list_date.push_back(Date());
	list_date.push_back(Date());
	list_date.push_back(Date());
	print(list_date);

}


void test_iterator()
{
	zwr::list<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);

	zwr::list<int>::iterator it = list.begin();
	while (it != list.end())
	{
		cout << *it << ' ';
		++it;
	}
	cout << endl;
	for (auto& e : list)
	{
		cout << ++e << ' ';
	}
	cout << endl;

	zwr::list<Date> list_date;
	list_date.push_back(Date());
	list_date.push_back(Date());
	list_date.push_back(Date());
	list_date.push_back(Date());

	auto dit = list_date.begin();
	cout << ++dit->_year;
	cout << ++dit->_month;
	cout << ++dit->_day;

	return;
}

void test_access()
{
	zwr::list<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);

	cout << list.front()<< ' ';
	cout << list.back();
}

void test_capacity()
{
	zwr::list<int> list;
	if (list.empty())
	{
		list.push_back(1);
		list.push_back(2);
		list.push_back(3);
		list.push_back(4);
		list.push_back(5);
	}
	cout << list.size();
}

void test_modifiers()
{
	zwr::list<int> list;
	list.push_back(5);
	list.push_back(4);
	list.push_back(3);
	list.push_back(2);
	list.push_back(1);
	
	zwr::list<int> tmp;
	tmp.push_back(1);
	tmp.push_back(2);
	tmp.push_back(3);
	tmp.push_back(4);
	tmp.push_back(5);

	list.swap(tmp);
	for (auto e : list)
	{
		cout << e << ' ';
	}
	cout << endl;
	for (auto e : tmp)
	{
		cout << e << ' ';
	}
	cout << endl;

	list.clear();
	if (list.empty())
	{
		cout << "empty" << endl;
	}

	list.push_front(5);
	list.push_front(4);
	list.push_front(3);
	list.push_front(2);
	list.push_front(1);
	for (auto& e : list)
	{
		cout << e << ' ';

	}
	cout << endl;
	list.pop_front();
	list.pop_front();
	list.pop_front();
	list.pop_front();
	list.pop_front();
	//list.pop_front();
	if (list.empty())
	{
		cout << "empty" << endl;
	}



}
void test_constructor()
{
	zwr::list<int> list1;
	list1.push_back(1);
	list1.push_back(2);
	list1.push_back(3);
	list1.push_back(4);
	list1.push_back(5);
	for (auto e : list1)
	{
		cout << e << ' ';
	}
	cout << endl;

	zwr::list<int> list2(list1);
	for (auto e : list2)
	{
		cout << e << ' ';
	}
	cout << endl;

	zwr::list<int> list3;
	list3 = list1;
	for (auto e : list3)
	{
		cout << e << ' ';
	}
	cout << endl;

	zwr::list<int> list4(list1.begin(), list1.end());
	for (auto e : list4)
	{
		cout << e << ' ';
	}
	cout << endl;



}

int main()
{
	//test_const_iterator();
	//test_iterator();
	//test_access();
	//test_capacity();
	//test_modifiers();
	test_constructor();


	return 0;
}


#include <iostream>
#include<vector>
#include "Vector.h"

using namespace std;


void test_std_vector()
{
	vector<string> v(10, "asdf");
	for(auto e : v)
	{
		cout << e << ' ';
	}
	cout << endl;

	vector<string> v1(v);
	for (auto e : v)
	{
		cout << e << ' ';
	}
	cout << endl;
	cout << v.size()<< ' ' << v.capacity() << endl;
	v.resize(3);
	cout << v.size() << ' ' << v.capacity() << endl;
	v.reserve(3);
	cout << v.size() << ' ' << v.capacity() << endl;
	v.reserve(11);
	cout << v.size() << ' ' << v.capacity() << endl;



}

void test_constructor()
{
	zwr::vector<string> v(10, "asdf");
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << ' ';
	}
	cout << endl;

	zwr::vector<string> v1(v);
	for (auto e : v)
	{
		cout << e << ' ';
	}
	cout << endl;
	cout << v.size() << ' ' << v.capacity() << endl;
	v.resize(3);
	cout << v.size() << ' ' << v.capacity() << endl;
	v.reserve(3);
	cout << v.size() << ' ' << v.capacity() << endl;
	v.reserve(11);
	cout << v.size() << ' ' << v.capacity() << endl;
}

int main()
{
	test_std_vector();
	test_constructor();
	return 0;
}
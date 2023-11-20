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

	vector<string>v2(v.begin(), v.end());
	for (auto e : v)
	{
		cout << e << ' ';
	}
	cout << endl;



	vector<string> v1(v);
	for (auto e : v1)
	{
		cout << e << ' ';
	}
	cout << endl;
	cout << v1.size()<< ' ' << v1.capacity() << endl;
	v1.resize(3);
	cout << v1.size() << ' ' << v1.capacity() << endl;
	v1.reserve(3);
	cout << v1.size() << ' ' << v1.capacity() << endl;
	v1.reserve(11);
	cout << v1.size() << ' ' << v1.capacity() << endl;



}

void test_constructor()
{
	//n个iterator构造
	zwr::vector<string> vs(10, "asdf");
	for (int i = 0; i < vs.size(); i++)
	{
		cout << vs[i] << ' ';
	}
	cout << endl;
	//iterator构造
	zwr::vector<string>vs2(vs.begin(), vs.end());
	for (auto e : vs2)
	{
		cout << e << ' ';
	}
	cout << endl;	
	//拷贝构造
	zwr::vector<string> vs1(vs); 
	for (auto e : vs1)
	{
		cout << e << ' ';
	}
	cout << endl;

	//深拷贝测试
	zwr::vector<int> v(10);
	for (int i = 0; i < 10; i++)
	{
		v[i] = i;
	}
	for (auto e : v)
	{
		cout << e << ' ';
	}
	cout << endl;
	zwr::vector<zwr::vector<int>> vv(10, v);
	for (int i = 0; i < vv.size(); i++)
	{
		for (int j = 0; j < vv[i].size(); j++)
		{
			cout << vv[i][j] << endl;
		}
		cout << endl;
	}
}

int main()
{
	//test_std_vector();
	test_constructor();
	return 0;
}
#include <iostream>
#include<vector>
#include "Vector.h"

using namespace std;


void test_std_vector()
{
	/*vector<string> v(10, "asdf");
	for(auto e : v)
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

	vector<string>v2(v.begin(), v.end());
	for (auto e : v)
	{
		cout << e << ' ';
	}
	cout << endl;*/

	vector<int> v3;
	v3.push_back(0);
	v3.push_back(1);
	v3.push_back(2);
	v3.push_back(3);
	auto it = v3.begin();
	while (!v3.empty())
	{
		 it = v3.erase(it);
	}
	if (v3.empty())
	{
		cout << "empty\n";
	}

	vector<int> v4;
	v4.push_back(0);
	v4.push_back(1);
	v4.push_back(2);
	v4.push_back(3);
	vector<int>::iterator it4 = v4.erase(v4.begin(), v4.end() - 1);
	cout << *it4;



}

void test_modifiers()
{
	//push_back
	zwr::vector<int> vi;
	vi.push_back(1);
	vi.push_back(2);
	vi.push_back(3);
	vi.push_back(4);
	//vi.push_back(5);
	// pop_back
	//vi.pop_back();
	for (auto e : vi)
	{
		cout << e << ' ';
	}
	cout << endl;


	//insert
	//头插
	auto it1 = vi.begin();
	vi.insert(it1, 0);
	for (auto e : vi)
	{
		cout << e << ' ';
	}
	cout << endl;

	zwr::vector<int>::iterator it2 = vi.begin();
	vi.insert(it2, 3, 0);
	for (auto e : vi)
	{
		cout << e << ' ';
	}
	cout << endl;

	//尾插
	auto it3 = vi.end();
	vi.insert(it3, 0);
	for (auto e : vi)
	{
		cout << e << ' ';
	}
	cout << endl;

	auto it4 = vi.end();
	vi.insert(it4, 5, 0);
	for (auto e : vi)
	{
		cout << e << ' ';
	}
	cout << endl;

	//erase
	auto it5 = vi.begin();
	it5 = vi.erase(it5);
	for (auto e : vi)
	{
		cout << e << ' ';
	}
	cout << endl;
	while (!vi.empty())
	{
		it5 = vi.erase(it5);
	}
	if (vi.empty())
	{
		cout << "empty\n";
	}

	vector<int> v6;
	v6.push_back(0);
	v6.push_back(1);
	v6.push_back(2);
	v6.push_back(3);
	vector<int>::iterator it6 = v6.erase(v6.begin(), v6.end() - 1);
	cout << *it6<<endl;

	//swap
	zwr::vector<int> v7;
	v7.push_back(1);
	v7.push_back(2);
	v7.push_back(3);
	v7.push_back(4);
	for (auto e : v7)
	{
		cout << e << ' ';
	}
	cout << endl;
	zwr::vector<int> v8;
	v8.push_back(4);
	v8.push_back(3);
	v8.push_back(2);
	v8.push_back(1);
	for (auto e : v8)
	{
		cout << e << ' ';
	}
	cout << endl;
	v7.swap(v8);
	for (auto e : v7)
	{
		cout << e << ' ';
	}
	cout << endl;
	for (auto e : v8)
	{
		cout << e << ' ';
	}
	cout << endl;
	//clear
	v7.clear();
	if (v7.empty())
	{
		cout << "empty\n";
	}
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
	/*zwr::vector<int> v(10);
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
	}*/
}

int main()
{
	//test_std_vector();
	//test_constructor();
	test_modifiers();
	return 0;
}
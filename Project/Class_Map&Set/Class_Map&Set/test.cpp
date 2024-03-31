#include <iostream>
#include "Map.h"
#include "Set.h"

#include <vector>
#include <map>


using namespace std;
using namespace zwr;


void SetTest1()
{
	Set<int> set;
	set.Insert(1);
	set.Insert(2);
	set.Insert(3);
	set.Insert(4);
	set.Insert(5);
	set.Insert(6);
	set.Insert(7);
	set.Insert(8);
	auto it = set.begin();

	while (it != set.end())
	{
		cout << *it << ' ';
		++it;
	}
	cout << endl;

}
void MapTest2()
{

	vector<vector<int>> test = {
		{10, 5, 15, 3, 8, 12, 18, 2, 4, 7, 9, 11, 13, 17, 19, 1, 6, 14, 16, 20},
		{20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
		{10, 8, 12, 6, 14, 4, 16, 2, 18, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 20},
		{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
		{20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 19, 17, 15, 13, 11, 9, 7, 5, 3, 1},
		{5, 3, 7, 2, 4, 6, 8, 1, 9, 10, 15, 12, 18, 11, 14, 17, 20, 13, 16, 19},
		{15, 10, 20, 5, 12, 18, 3, 7, 2, 4, 6, 8, 1, 9, 11, 13, 14, 16, 17, 19},
		{13, 17, 12, 18, 11, 19, 10, 20, 9, 14, 8, 15, 7, 16, 6, 5, 4, 3, 2, 1}
	};
	for (int i = 0; i < test.size(); i++)
	{
		Map<int, int> map;
		for (int j = 0; j < test[0].size(); j++)
		{
			map.Insert(make_pair(test[i][j], test[i][j]));
			/*if (rbt.IsRBT())
				cout << "Is RBT!" << endl;*/
		}
		Map<int, int>::iterator it = map.begin();
		while (it != map.end())
		{
			cout << (*it).second << ' ';
			++it;
		}
		cout << endl;
	}
}

void MapTest1()
{
	Map<int, int> map;

	map.Insert(make_pair(5, 5));
	map.Insert(make_pair(3, 3));
	map.Insert(make_pair(7, 7));
	map.Insert(make_pair(2, 2));
	map.Insert(make_pair(4, 4));
	map.Insert(make_pair(6, 6));
	map.Insert(make_pair(8, 8));
	map.Insert(make_pair(1, 1));
	Map<int, int>::iterator it = map.begin();
	while (it != map.end())
	{
		cout << (*it).second << ' ';
		++it;
	}

}

void StdMapTest()
{
	map<int, int> m;
	m.insert(make_pair(5, 5));
	m.insert(make_pair(3, 3));
	m.insert(make_pair(7, 7));
	m.insert(make_pair(2, 2));
	m.insert(make_pair(4, 4));
	m.insert(make_pair(6, 6));
	m.insert(make_pair(8, 8));
	auto c = m.insert(make_pair(1, 1));

	auto it = m.begin();
	/*for (auto& e : m)
	{
		cout << e << ' ';
	}*/

	while (it != m.end())
	{
		cout << it->second << ' ';
		it++;
	}
	cout << endl;

}



int main()
{
	StdMapTest();

	MapTest1();
	MapTest2();
	SetTest1();
	return 0;
}
#include <iostream>
#include "Set.h"
#include "Map.h"
#include <vector>

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
	//set.InOrder();

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


int main()
{
	MapTest1();
	SetTest1();
	return 0;
}
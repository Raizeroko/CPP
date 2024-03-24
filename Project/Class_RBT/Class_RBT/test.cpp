#include "RBT.h"
#include <iostream>
#include <vector>


using namespace std;
using namespace zwr;


// 100个随机数测试
void RBTTest3()
{
	std::vector<int> randomNumbers;

	// 设置种子
	std::srand(std::time(nullptr));

	// 生成随机数
	for (int i = 0; i < 100; ++i) {
		int randomNumber = std::rand() % 1000; // 生成0到999之间的随机数
		randomNumbers.push_back(randomNumber);
	}

	RBTree<int, int> rbt;
	for (int i = 0; i < randomNumbers.size(); i++)
	{
		rbt.Insert(make_pair(randomNumbers[i], randomNumbers[i]));
		
	}

	rbt.InOrder();
	if (rbt.IsRBT())
		cout << "Is RBT!" << endl;


}


// 多测试用例
void RBTTest2()
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
		RBTree<int, int> rbt;
		for (int j = 0; j < test[0].size(); j++)
		{
			rbt.Insert(make_pair(test[i][j], test[i][j]));
			/*if (rbt.IsRBT())
				cout << "Is RBT!" << endl;*/
		}
		rbt.InOrder();
		if (rbt.IsRBT())
			cout << "Is RBT!" << endl;
	}

}


void RBTTest1()
{
	RBTree<int, int> rbt;
	rbt.Insert(make_pair(5, 5));
	rbt.Insert(make_pair(3, 3));
	rbt.Insert(make_pair(7, 7));
	rbt.Insert(make_pair(2, 2));
	rbt.Insert(make_pair(4, 4));
	rbt.Insert(make_pair(6, 6));
	rbt.Insert(make_pair(8, 8));
	rbt.Insert(make_pair(1, 1));
	rbt.InOrder();
	if (rbt.IsRBT())
		cout << "Is RBT!" << endl;


}


int main()
{
	//RBTTest1();
	//RBTTest2();
	RBTTest3();
	return 0;
}

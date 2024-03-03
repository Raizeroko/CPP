#include "AVL.h"

using namespace zwr;
using namespace std;

void AVLTest1()
{
	cout << "test1��" << endl;
	//����ת�������
	AVLTree<int,int> avl;
	avl.Insert(make_pair(5, 5));
	cout << avl.GetValue() << endl;
	avl.Insert(make_pair(3, 3));
	avl.Insert(make_pair(8, 8));
	avl.Insert(make_pair(2, 2));
	avl.Insert(make_pair(4, 4));
	avl.Insert(make_pair(6, 6));
	avl.Insert(make_pair(9, 9));
	avl.InOrder();
	cout << endl;
}

void AVLTest2()
{
	//��������
	cout << "test2��" << endl;
	AVLTree<int,int> avl;
	avl.Insert(make_pair(5, 5));
	cout << avl.GetValue() << endl;
	avl.Insert(make_pair(3, 3));
	avl.Insert(make_pair(2, 2));
	avl.Insert(make_pair(7, 7));
	avl.Insert(make_pair(8, 8));
	avl.InOrder();
	cout << endl;
}

void AVLTest3()
{
	//�ۺϲ���
	cout << "test3��" << endl;
	AVLTree<int, int> avl1;
	avl1.Insert(make_pair(16, 16));
	avl1.Insert(make_pair(3, 3));
	avl1.Insert(make_pair(7, 7));
	avl1.Insert(make_pair(11, 11));
	avl1.Insert(make_pair(9, 9));
	avl1.Insert(make_pair(26, 26));
	avl1.Insert(make_pair(18, 18));
	avl1.Insert(make_pair(14, 14));
	avl1.Insert(make_pair(15, 15));
	avl1.InOrder();
	if (avl1.IsBalance())
		cout << "Is AVL!!" << endl;

	AVLTree<int, int> avl2;
	avl2.Insert(make_pair(4, 4));
	avl2.Insert(make_pair(2, 2));
	avl2.Insert(make_pair(6, 6));
	avl2.Insert(make_pair(1, 1));
	avl2.Insert(make_pair(3, 3));
	avl2.Insert(make_pair(5, 5));
	avl2.Insert(make_pair(15, 15));
	avl2.Insert(make_pair(7, 7));
	avl2.Insert(make_pair(16, 16));
	avl2.Insert(make_pair(14, 14));
	avl2.InOrder();

	if (avl2.IsBalance())
		cout << "Is AVL!!" << endl;
	cout << endl;
}

int main()
{
	AVLTest1();
	AVLTest2();
	AVLTest3();
	return 0;
}
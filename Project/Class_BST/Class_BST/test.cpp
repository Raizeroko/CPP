#include"BSTKey.h"
#include"BSTKeyValue.h"


using namespace zwr;
using namespace std;

void BSTKeyTest1()
{
	//BST·ÇµÝ¹é
	BSTKey<int> bst;
	auto find = bst.Find(1);
	if (find)
		cout << find->_key << endl;
	else
		cout << "can't find, ptr is nullptr" << endl;
	bst.Insert(3);
	bst.Insert(8);
	bst.Insert(7);
	bst.Insert(2);
	bst.Insert(6);
	bst.Insert(9);
	bst.Insert(1);
	bst.Insert(5);
	bst.Insert(4);
	find = bst.Find(5);
	if (find)
		cout << find->_key << endl;
	bst.InOrder();
	cout << "Erase²âÊÔ" << endl;
	//Erase²âÊÔ
	bst.Erase(3);
	bst.InOrder();
	bst.Erase(7);
	bst.InOrder();
	bst.Erase(8);
	bst.InOrder();
	bst.Erase(2);
	bst.InOrder();
	bst.Erase(1);
	bst.InOrder();
	bst.Erase(5);
	bst.InOrder();
	bst.Erase(9);
	bst.InOrder();
	bst.Erase(7);
	bst.InOrder();
	bst.Erase(4);
	bst.InOrder();
	bst.Erase(6);
	bst.InOrder();
}

void BSTKeyTest2()
{
	//BSTµÝ¹é
	BSTKey<int> bst;
	auto find = bst.Find(1);
	if (find)
		cout << find->_key << endl;
	else
		cout << "can't find, ptr is nullptr" << endl;
	bst.InsertRecursion(3);
	bst.InsertRecursion(8);
	bst.InsertRecursion(7);
	bst.InsertRecursion(2);
	bst.InsertRecursion(6);
	bst.InsertRecursion(9);
	bst.InsertRecursion(1);
	bst.InsertRecursion(5);
	bst.InsertRecursion(4);
	find = bst.FindRecursion(5);
	if (find)
		cout << find->_key << endl;
	bst.InOrder();
	cout << "Erase²âÊÔ" << endl;
	//Erase²âÊÔ
	bst.EraseRecursion(3);
	bst.InOrder();
	bst.EraseRecursion(7);
	bst.InOrder();
	bst.EraseRecursion(8);
	bst.InOrder();
	bst.EraseRecursion(2);
	bst.InOrder();
	bst.EraseRecursion(1);
	bst.InOrder();
	bst.EraseRecursion(5);
	bst.InOrder();
	bst.EraseRecursion(9);
	bst.InOrder();
	bst.EraseRecursion(7);
	bst.InOrder();
	bst.EraseRecursion(4);
	bst.InOrder();
	bst.EraseRecursion(6);
	bst.InOrder();
}

void BSTKeyValueTest1()
{
	BSTKeyValue<int, int> bst;
	auto find = bst.Find(1);
	if (find)
		cout << find->_key << endl;
	else
		cout << "can't find, ptr is nullptr" << endl;
	bst.Insert(3, 3);
	bst.Insert(8, 8);
	bst.Insert(7, 7);
	bst.Insert(2, 2);
	bst.Insert(6, 6);
	bst.Insert(9, 9);
	bst.Insert(1, 1);
	bst.Insert(5, 5);
	bst.Insert(4, 4);
	find = bst.Find(5);
	if (find)
		cout << find->_key << endl;
	bst.InOrder();
	cout << "Erase²âÊÔ" << endl;
	//Erase²âÊÔ
	bst.Erase(3);
	bst.InOrder();
	bst.Erase(7);
	bst.InOrder();
	bst.Erase(8);
	bst.InOrder();
	bst.Erase(2);
	bst.InOrder();
	bst.Erase(1);
	bst.InOrder();
	bst.Erase(5);
	bst.InOrder();
	bst.Erase(9);
	bst.InOrder();
	bst.Erase(7);
	bst.InOrder();
	bst.Erase(4);
	bst.InOrder();
	bst.Erase(6);
	bst.InOrder();
}

void BSTKeyValueTest2()
{
	//BSTµÝ¹é
	BSTKeyValue<int, int> bst;
	auto find = bst.Find(1);
	if (find)
		cout << find->_key << endl;
	else
		cout << "can't find, ptr is nullptr" << endl;
	bst.InsertRecursion(3, 3);
	bst.InsertRecursion(8, 8);
	bst.InsertRecursion(7, 7);
	bst.InsertRecursion(2, 2);
	bst.InsertRecursion(6, 6);
	bst.InsertRecursion(9, 9);
	bst.InsertRecursion(1, 1);
	bst.InsertRecursion(5, 5);
	bst.InsertRecursion(4, 4);
	find = bst.FindRecursion(5);
	if (find)
		cout << find->_key << endl;
	bst.InOrder();
	cout << "Erase²âÊÔ" << endl;
	//Erase²âÊÔ
	bst.EraseRecursion(3);
	bst.InOrder();
	bst.EraseRecursion(7);
	bst.InOrder();
	bst.EraseRecursion(8);
	bst.InOrder();
	bst.EraseRecursion(2);
	bst.InOrder();
	bst.EraseRecursion(1);
	bst.InOrder();
	bst.EraseRecursion(5);
	bst.InOrder();
	bst.EraseRecursion(9);
	bst.InOrder();
	bst.EraseRecursion(7);
	bst.InOrder();
	bst.EraseRecursion(4);
	bst.InOrder();
	bst.EraseRecursion(6);
	bst.InOrder();
}



int main()
{
	cout << "BSTKetValue Test" << endl;
	BSTKeyTest1();
	BSTKeyTest2();
	cout << "BSTKeyValue Test" << endl;
	BSTKeyValueTest1();
	BSTKeyValueTest2();
	return 0;
}
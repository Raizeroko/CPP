# include<iostream>
# include<queue>

using namespace std;

class BinaryTree{
public:
	typedef int value_type;

	BinaryTree()
		: _val(0)
		, _left(nullptr)
		, _right(nullptr)
	{}

	//(1)
	int leaf_num()
	{
		//是空结点
		if (this == nullptr)
		{
			return 0;
		}
		//是叶子
		if (_left == nullptr && _right == nullptr)
		{
			return 1;
		}
		else
		{
			return _left->leaf_num() + _right->leaf_num();
		}
	}
	//(2)
	bool operator== (BinaryTree* bt)
	{
		if (this == nullptr && bt == nullptr)
		{
			return true;
		}
		else if (this == nullptr || bt == nullptr)
		{
			return false;
		}
		if (_val == bt->_val)
		{
			return (_left == bt->_left) && (_right == bt->_right);
		}
		else
		{
			return false;
		}
	}
	//(3)
	void exchange_node()
	{
		if (this == nullptr)
			return;
		_left->exchange_node();
		_right->exchange_node();
		BinaryTree* tmp = _left;
		_left = _right;
		_right = tmp;
	}
	//(4)
	void double_order_traverse()
	{
		if (this)
		{
			cout << _val;
			_left->exchange_node();
			cout << _val;
			_right->exchange_node();
		}
	}
	//(5)
	int _max_width(stack& h)
	{
		;
	}
	int max_width()
	{

	}

private:
	value_type _val;
	BinaryTree* _left;
	BinaryTree* _right;
};
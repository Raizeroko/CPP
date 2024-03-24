#pragma once

#include <iostream>

namespace zwr {
	enum TreeNodeColor
	{
		RED,
		BLACK
	};

	template<class K, class V>
	struct RBTreeNode {
		RBTreeNode(const std::pair<K,V>& kv)
			:_kv(kv)
			,_color(RED)
			,_left(nullptr)
			,_right(nullptr)
			,_father(nullptr)
		{}
		std::pair<K, V> _kv;
		TreeNodeColor _color;
		RBTreeNode<K, V>* _left;
		RBTreeNode<K, V>* _right;
		RBTreeNode<K, V>* _father;
	};

	template<class K, class V>
	class RBTree {
		typedef RBTreeNode<K, V> Node;
	public:
		RBTree()
			:_root(nullptr)
		{}

		bool Insert(std::pair<K, V> kv)
		{
			if (_root == nullptr)
			{
				_root = new Node(kv);
				_root->_color = BLACK;
				return true;
			}
			Node* father = nullptr;
			Node* child = _root;

			while (child)
			{
				if (kv.first < child->_kv.first)
				{
					father = child;
					child = child->_left;
				}
				else if (kv.first > child->_kv.first)
				{
					father = child;
					child = child->_right;
				}
				else
				{
					return false;
				}

			}

			child = new Node(kv);
			if (kv.first < father->_kv.first)
			{
				father->_left = child;
			}
			else 
			{
				father->_right = child;
			}
			child->_father = father;
			// 连续红节点则不满足红黑树条件
			while (father && father->_color == RED)
			{
				Node* grandFather = father->_father;
				if (grandFather == nullptr)
					break;
				Node* uncle = grandFather->_left;
 				if (uncle == father)
				{
					uncle = grandFather->_right;
				}
				// 1.uncle为红，则uncle, grandFather, father全换色
				if (uncle && uncle->_color == RED)
				{
					uncle->_color = BLACK;
					father->_color = BLACK;
					grandFather->_color = RED;
					child = grandFather;
					father = child->_father;
				}
				// 2.uncle为黑，则需要旋转
				else
				{
					if (grandFather->_left)
					{
						if (grandFather->_left->_left && grandFather->_left->_left == child)
						{
							_RotateR(father);
						}
						else if (grandFather->_left->_right && grandFather->_left->_right == child)
						{
							_RotateLR(father);
						}
					}
					if (grandFather->_right)
					{
						if (grandFather->_right->_right && grandFather->_right->_right == child)
						{
							_RotateL(father);
						}
						else if (grandFather->_right->_left && grandFather->_right->_left == child)
						{
							_RotateRL(father);
						}
					}
					break;
				}
			}
			_root->_color = BLACK;
			return true;
		}

		

		void InOrder()
		{
			_InOrder(_root);
			std::cout << std::endl;
		}

		bool IsRBT()
		{
			return _IsRBT(_root);
		}
		~RBTree()
		{
			_Destroy(_root);
			_root == nullptr;
		}


	protected:
		void _InOrder(Node* cur)
		{
			if (cur == nullptr)
				return;
			_InOrder(cur->_left);
			std::cout << cur->_kv.second << ' ';
			_InOrder(cur->_right);
		}
		void _RotateR(Node* child)
		{
			Node* father = child->_father;
			Node* grandFather = father->_father;
			Node* grandChildR = child->_right;

			child->_father = grandFather;
			//如果grandFather不为空，要进行连接
			if (grandFather)
			{
				if (grandFather->_left == father)
				{
					grandFather->_left = child;
				}
				else
				{
					grandFather->_right = child;
				}
			}
			else
			{
				_root = child;
			}
			child->_right = father;
			father->_father = child;
			father->_left = grandChildR;
			if(grandChildR)
				grandChildR->_father = father;

			//更新颜色
			child->_color = BLACK;
			father->_color = RED;
		}
		void _RotateL(Node* child)
		{
			Node* father = child->_father;
			Node* grandFather = father->_father;
			Node* grandChildL = child->_left;

			child->_father = grandFather;
			//如果grandFather不为空，要进行连接
			if (grandFather)
			{
				if (grandFather->_left == father)
				{
					grandFather->_left = child;
				}
				else
				{
					grandFather->_right = child;
				}
			}
			else
			{
				_root = child;
			}
			child->_left = father;
			father->_father = child;
			father->_right = grandChildL;
			if (grandChildL)
				grandChildL->_father = father;

			//更新颜色
			child->_color = BLACK;
			father->_color = RED;
		}
		void _RotateLR(Node* child)
		{
			Node* grandChildR = child->_right;
			Node* father = child->_father;
			// 先左旋再右旋
			_RotateL(grandChildR);
			_RotateR(grandChildR);

			father->_color = RED;
			grandChildR->_color = BLACK;

		}
		void _RotateRL(Node* child)
		{
			Node* grandChildL = child->_left;
			Node* father = child->_father;

			_RotateR(grandChildL);
			_RotateL(grandChildL);

			father->_color = RED;
			grandChildL->_color = BLACK;
		}


		bool _IsRBT(Node* _root)
		{
			return _root->_color == BLACK && _SameBlack(_root) && _DoubleRed(_root);
		}

		bool _DoubleRed(Node* cur)
		{
			if (cur == nullptr)
				return true;
			if (cur->_father && cur->_color == RED && cur->_father->_color == RED)
				return false;
			else
				return _DoubleRed(cur->_left) && _DoubleRed(cur->_right);
		}

		bool _SameBlack(Node* cur)
		{
			int numBlack = _NumBlack(cur);
			return numBlack != -1;
		}
		int _NumBlack(Node* cur)
		{
			if (cur == nullptr)
			{
				return 1;
			}
			int numLeft = _NumBlack(cur->_left);
			int numRight = _NumBlack(cur->_right);
			if (numLeft != numRight)
				return -1;
			else
				return cur->_color == BLACK ? numLeft + 1 : numLeft;
		}
		void _Destroy(Node* cur)
		{
			if (cur == nullptr)
				return;
			_Destroy(cur->_left);
			_Destroy(cur->_right);
			delete cur;
		}


	private:
		Node* _root;
	};

}
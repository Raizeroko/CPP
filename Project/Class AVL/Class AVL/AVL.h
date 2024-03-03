#pragma once

#include<iostream>

namespace zwr {
	template<class K, class V>
	struct AVLTreeNode {
		AVLTreeNode(const std::pair<K, V>& kv)
			:_kv(kv)
			, _bf(0)
			, _left(nullptr)
			, _right(nullptr)
			, _parent(nullptr)
		{}

		std::pair<K, V> _kv;
		int _bf; //balence factor,右子树减左子树
		AVLTreeNode<K, V>* _left;
		AVLTreeNode<K, V>* _right;
		AVLTreeNode<K, V>* _parent;
	};

	template<class K, class V>
	class AVLTree {
		typedef AVLTreeNode<K, V> Node;
	
	public:
		AVLTree()
			:_root(nullptr)
		{}
		
		const V& GetValue()
		{
			return _root->_kv.second;
		}

		bool Insert(const std::pair<K, V>& kv)
		{
			if (_root == nullptr)
			{
				_root = new Node(kv);
				return true;
			}
			Node* father = nullptr;
			Node* child = _root;
			//找插入位置
			while (child)
			{
				if (kv.first < child->_kv.first)
				{
					father = child;
					child = child->_left;
				}
				else
				{
					father = child;
					child = child->_right;
				}
			}
			//按BST插入 
			child = new Node(kv);
			if (kv.first < father->_kv.first)
			{
				father->_left = child;
				child->_parent = father;
			}
			else
			{
				father->_right = child;
				child->_parent = father;
			}
			//检查balance factor
			while (father)
			{
				//更新平衡因子
				if (father->_left == child)
					father->_bf--;
				else if (father->_right == child)
					father->_bf++;
				//1.插入后平衡因子为0,完成插入
				if (father->_bf == 0)
					break;
				//2.插入后平衡因子为-1或1，往上更新平衡因子
				else if (father->_bf == -1 || father->_bf == 1)
				{
					child = father;
					father = father->_parent;
				}
				//3.插入后平衡因子为-2或2，旋转
				else if (father->_bf == 2 || father->_bf == -2)
				{
					//右单旋
					if (father->_bf == -2 && child->_bf == -1)
					{
						_RotateR(child);
					}
					//左单旋
					else if (father->_bf == 2 && child->_bf == 1)
					{
						_RotateL(child);
					}
					//左右双旋
					else if (father->_bf == -2 && child->_bf == 1)
					{
						_RotateLR(child);
					}
					//右左双旋
					else if (father->_bf == 2 && child->_bf == -1)
					{
						_RotateRL(child);
					}
					else
					{
						return false;
					}
					break;
				}
				else
				{
					return false;
				}
			}
			return true;
		}

		void InOrder()
		{
			_InOrder(_root);
			std::cout << std::endl;
		}

		bool IsBalance()
		{
			return _IsBalance(_root);
		}

	protected:
		//右单旋
		void _RotateR(Node* child)
		{
			
			Node* father = child->_parent;
			Node* grandChildR = child->_right;
			Node* grandFather = father->_parent;

			child->_parent = grandFather;

			//如果grandFather不为空需要与child连接
			if (grandFather)
			{
				if (grandFather->_left == father)
					grandFather->_left = child;
				else
					grandFather->_right = child;
			}
			else
			{
				_root = child;
			}
			father->_parent = child;

			father->_left = grandChildR;
			child->_right = father;

			//如果grandChildR不为空需要与father连接
			if (grandChildR)
				grandChildR->_parent = father;

			//更新balance factor
			father->_bf = child->_bf = 0;
		}

		//左单旋
		void _RotateL(Node* child)
		{
			Node* father = child->_parent;
			Node* grandChildL = child->_left;
			Node* grandFather = father->_parent;

			child->_parent = grandFather;

			//如果grandFather不为空需要与child连接
			if (grandFather)
			{
				if (grandFather->_left == father)
					grandFather->_left = child;
				else
					grandFather->_right = child;
			}
			else
			{
				_root = child;
			}
			father->_parent = child;

			father->_right = grandChildL;
			child->_left = father;

			//如果grandChildL不为空需要与father连接
			if (grandChildL)
				grandChildL->_parent = father;

			//更新balance factor
			father->_bf = child->_bf = 0;
		}

		//左右双旋
		void _RotateLR(Node* child)
		{
			Node* father = child->_parent;
			Node* grandChildR = child->_right;
			
			int bf = grandChildR->_bf;
			//左单旋子孙
			_RotateL(grandChildR);
			//右单旋父孙
			_RotateR(grandChildR);

			//更新balace factor
			if (bf == -1)
				father->_bf = 1;
			else if (bf == 1)
				child->_bf = -1;
		}

		//右左双旋
		void _RotateRL(Node* child)
		{
			Node* father = child->_parent;
			Node* grandChildL = child->_left;
			int bf = grandChildL->_bf;

			//右单旋子孙
			_RotateR(grandChildL);
			//左单旋父孙
			_RotateL(grandChildL);

			//更新balance factor
			if (bf == 1)
				father->_bf = 1;
			else if (bf == -1)
				child->_bf = -1;
		}

		void _InOrder(Node* cur)
		{
			if (cur == nullptr)
				return;
			_InOrder(cur->_left);
			std::cout << cur->_kv.second << ' ';
			_InOrder(cur->_right);
		}

		int _Height(Node* cur)
		{
			if (cur == nullptr)
				return 0;
			else
			{
				int leftHeight = _Height(cur->_left) + 1;
				int rightHeight = _Height(cur->_right) + 1;
				return leftHeight > rightHeight ? leftHeight : rightHeight;
			}

		}

		bool _IsBalance(Node* cur)
		{
			if (cur == nullptr)
				return true;
			int leftHeight = _Height(cur->_left);
			int rightHeight = _Height(cur->_right);
			int bf = rightHeight - leftHeight;
			if (bf == cur->_bf && bf >= -1 && bf <= 1)
				return true;
			else
				return false;
			return _IsBalance(cur->_left) && _IsBalance(cur->_right);
		}

	private:
		Node* _root;
	};
}

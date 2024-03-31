#pragma once

#pragma once
#include <iostream>

namespace zwr {
	enum TreeNodeColor
	{
		RED,
		BLACK
	};

	template<class T>
	struct RBTreeNode {
		RBTreeNode(const T& kv)
			: _kv(kv)
			, _color(RED)
			, _left(nullptr)
			, _right(nullptr)
			, _father(nullptr)
		{}
		T _kv;
		TreeNodeColor _color;
		RBTreeNode<T>* _left;
		RBTreeNode<T>* _right;
		RBTreeNode<T>* _father;
	};

	template<class T, class Ref, class Ptr>
	struct _RBTreeIterator {
		typedef RBTreeNode<T> Node;
		typedef _RBTreeIterator<T, Ref, Ptr> Self;
		Node* _iter;

		_RBTreeIterator(Node* node)
			:_iter(node)
		{}

		Ref operator*()
		{
			return _iter->_kv;
		}

		Ptr operator->()
		{
			return &(_iter->_kv);
		}

		Self& operator++()
		{
			if (_iter->_right)
			{
				//右子树最左
				Node* cur = _iter->_right;
				while (cur->_left)
				{
					cur = cur->_left;
				}
				_iter = cur;
				return *this;
			}
			else
			{
				Node* cur = _iter->_father;
				Node* prev = _iter;
				while (cur&& cur->_right == prev)
				{
					prev = cur;
					cur = cur->_father;
				}
				_iter = cur;
				return *this;
			}
		}
		Self& operator--()
		{
			if (_iter->_left)
			{
				//左子树最右
				Node* cur = _iter->_left;
				while (cur->_right)
				{
					cur = cur->_right;
				}
				_iter = cur;
				return *this;
			}
			else
			{
				Node* cur = _iter->_father;
				Node* prev = _iter;
				while (cur&& cur->_left = prev)
				{
					prev = cur;
					cur = cur->_father;
				}
				_iter = cur;
				return *this;
			}
		}

		bool operator!=(const Self& s)
		{
			return _iter != s._iter;
		}

	};

	template<class K, class T, class KeyOfT>
	class RBTree {
		typedef RBTreeNode<T> Node;
	public:
		typedef _RBTreeIterator<T, T&, T*> iterator;
		typedef _RBTreeIterator<T, const T&, const T*> const_iterator;

		iterator begin()
		{
			Node* cur = _root;
			while (cur && cur->_left)
			{
				cur = cur->_left;
			}
			return iterator(cur);
		}
		iterator end()
		{
			return nullptr;
		}
		const_iterator begin() const
		{
			Node* cur = _root;
			while (cur && cur->_left)
			{
				cur = cur->_left;
			}
			return const_iterator(cur);
		}
		const_iterator end() const
		{
			return const_iterator(nullptr);
		}


		RBTree()
			:_root(nullptr)
		{}

		std::pair<const_iterator, bool> Insert(const T& kv)
		{
			if (_root == nullptr)
			{
				_root = new Node(kv);
				_root->_color = BLACK;
				return std::make_pair(const_iterator(_root), true);
			}
			Node* father = nullptr;
			Node* child = _root;

			KeyOfT kot;
			while (child)
			{
				const K& left = kot(kv);
				const K& right = kot(child->_kv);
				if (left < right)
				{
					father = child;
					child = child->_left;
				}
				else if (kot(kv) > kot(child->_kv))
				{
					father = child;
					child = child->_right;
				}
				else
				{
					return std::make_pair(const_iterator(nullptr), false);
				}

			}

			child = new Node(kv);
			if (kot(kv) < kot(father->_kv))
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
			return std::make_pair(const_iterator(child), true);
		}

		Node* Find(const K& key)
		{
			Node* cur = _root;
			while (cur)
			{
				if (key < kot(cur->_kv))
				{
					cur = cur->_left;
				}
				else if (key > kot(cur->_kv))
				{
					cur = cur->_right;
				}
				else if (key == kot(cur->_kv))
				{
					return cur;
				}
			}
			return nullptr;
		}

		/*void InOrder()
		{
			_InOrder(_root);
			std::cout << std::endl;
		}*/

		bool IsRBT()
		{
			return _IsRBT(_root);
		}
		~RBTree()
		{
			_Destroy(_root);
			_root = nullptr;
		}


	protected:
		/*void _InOrder(Node* cur)
		{
			if (cur == nullptr)
				return;
			KeyOfT kot;
			_InOrder(cur->_left);
			std::cout << kot(cur->_kv) << ' ';
			_InOrder(cur->_right);
		}*/
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
			if (grandChildR)
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
#pragma once
#include <iostream>


namespace zwr {

	template<class K, class V>
	struct BSTreeKeyValueNode {
		BSTreeKeyValueNode(const K& key, const V& value)
			:_left(nullptr)
			, _right(nullptr)
			, _key(key)
			, _value(value)
		{}
		BSTreeKeyValueNode<K,V>* _left;
		BSTreeKeyValueNode<K,V>* _right;
		K _key;
		V _value;
	};

	template<class K, class V>
	class BSTKeyValue {
		typedef BSTreeKeyValueNode<K, V> Node;

	public:
		BSTKeyValue()
			:_root(nullptr)
		{}

		//Insert,InOrder,Erase,Find
		bool Insert(const K& key, const V& value)
		{
			if (_root == nullptr)
			{
				_root = new Node(key, value);
				return true;
			}
			else
			{
				Node* prev = nullptr;
				Node* cur = _root;
				//找插入位置
				while (cur)
				{
					prev = cur;
					if (key < cur->_key)
					{
						cur = cur->_left;
					}
					else
					{
						cur = cur->_right;
					}
				}
				//创建新结点插入
				cur = new Node(key, value);
				if (key < prev->_key)
				{
					prev->_left = cur;
				}
				else
				{
					prev->_right = cur;
				}
				return true;
			}
			return false;
		}
		Node* Find(const K& key)
		{
			Node* cur = _root;
			while (cur)
			{
				if (key < cur->_key)
					cur = cur->_left;
				else if (key > cur->_key)
					cur = cur->_right;
				else
					break;
			}
			return cur;
		}
		bool Erase(const K& key)
		{
			if (_root == nullptr)
				return false;
			Node* prev = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (key < cur->_key)
				{
					prev = cur;
					cur = cur->_left;
				}
				else if (key > cur->_key)
				{
					prev = cur;
					cur = cur->_right;
				}
				else
				{
					//找到要删除的key
					//1.cur是叶子结点直接删除
					//2.cur左子树为空，右子树不为空，将cur右子树给prev，删除结点
					if (cur->_left == nullptr)
					{
						if (_root == cur)
							_root = cur->_right;
						else if (prev->_left == cur)
							prev->_left = cur->_right;
						else
							prev->_right = cur->_right;
						delete cur;
						return true;
					}
					//3.cur右子树为空
					else if (cur->_right == nullptr)
					{
						if (_root == cur)
							_root = cur->_left;
						else if (prev->_left == cur)
							prev->_left = cur->_left;
						else
							prev->_right = cur->_left;
						delete cur;
						return true;
					}
					//4.cur左右子树都不为空
					else
					{
						//找右树最小，或者左树最大
						Node* rightMin = cur->_right;
						Node* prevRightMin = cur;
						while (rightMin->_left)
						{
							prevRightMin = rightMin;
							rightMin = rightMin->_left;
						}
						if (rightMin == cur->_right)
						{
							cur->_right = rightMin->_right;
						}
						else
						{
							prevRightMin->_left = rightMin->_right;
						}
						cur->_key = rightMin->_key;
						delete rightMin;
						return true;
					}
				}
			}
			return false;
		}
		Node* FindRecursion(const K& key)
		{
			return _FindRecursion(_root, key);
		}
		bool InsertRecursion(const K& key, const V& value)
		{
			return _InsertRecursion(_root, key, value);
		}
		bool EraseRecursion(const K& key)
		{
			return _EraseRecursion(_root, key);
		}
		void InOrder()
		{
			_InOrder(_root);
			std::cout << std::endl;
		}


	private:
		void _InOrder(Node* cur)
		{
			if (cur == nullptr)
				return;
			_InOrder(cur->_left);
			std::cout << cur->_key << ' ';
			_InOrder(cur->_right);
		}
		Node* _FindRecursion(Node* cur, const K& key)
		{
			if (cur == nullptr)
				return nullptr;
			if (key < cur->_key)
				return _FindRecursion(cur->_left, key);
			else if (key > cur->_key)
				return _FindRecursion(cur->_right, key);
			return cur;
		}
		bool _InsertRecursion(Node*& cur, const K& key, const V& value)
		{
			if (cur == nullptr)
			{
				cur = new Node(key, value);
				return true;
			}
			if (key < cur->_key)
				return _InsertRecursion(cur->_left, key, value);
			else if (key > cur->_key)
				return _InsertRecursion(cur->_right, key, value);
			return false;
		}
		bool _EraseRecursion(Node*& cur, const K& key)
		{
			if (cur == nullptr)
				return false;
			if (key < cur->_key)
				return _EraseRecursion(cur->_left, key);
			else if (key > cur->_key)
				return _EraseRecursion(cur->_right, key);

			//找到要删除的结点
			//1.cur是叶子结点直接删除
			//2.cur左子树为空，右子树不为空，将cur右子树给prev，删除结点
			if (cur->_left == nullptr)
			{
				Node* erase = cur;
				cur = cur->_right;
				delete erase;
				return true;
			}
			//3.cur右子树为空
			else if (cur->_right == nullptr)
			{
				Node* erase = cur;
				cur = cur->_left;
				delete erase;
				return true;
			}
			//4.cur左右子树都不为空
			else
			{
				//找右树最小，或者左树最大
				Node* rightMin = cur->_right;
				while (rightMin->_left)
				{
					rightMin = rightMin->_left;
				}
				std::swap(cur->_key, rightMin->_key);
				return _EraseRecursion(cur->_right, key);
			}
			return false;
		}

		void _InOrder()
		{
			_InOrder(_root);
			std::cout << std::endl;
		}
	private:
		Node* _root;
	};
}
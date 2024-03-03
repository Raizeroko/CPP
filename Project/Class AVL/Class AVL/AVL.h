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
		int _bf; //balence factor,��������������
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
			//�Ҳ���λ��
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
			//��BST���� 
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
			//���balance factor
			while (father)
			{
				//����ƽ������
				if (father->_left == child)
					father->_bf--;
				else if (father->_right == child)
					father->_bf++;
				//1.�����ƽ������Ϊ0,��ɲ���
				if (father->_bf == 0)
					break;
				//2.�����ƽ������Ϊ-1��1�����ϸ���ƽ������
				else if (father->_bf == -1 || father->_bf == 1)
				{
					child = father;
					father = father->_parent;
				}
				//3.�����ƽ������Ϊ-2��2����ת
				else if (father->_bf == 2 || father->_bf == -2)
				{
					//�ҵ���
					if (father->_bf == -2 && child->_bf == -1)
					{
						_RotateR(child);
					}
					//����
					else if (father->_bf == 2 && child->_bf == 1)
					{
						_RotateL(child);
					}
					//����˫��
					else if (father->_bf == -2 && child->_bf == 1)
					{
						_RotateLR(child);
					}
					//����˫��
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
		//�ҵ���
		void _RotateR(Node* child)
		{
			
			Node* father = child->_parent;
			Node* grandChildR = child->_right;
			Node* grandFather = father->_parent;

			child->_parent = grandFather;

			//���grandFather��Ϊ����Ҫ��child����
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

			//���grandChildR��Ϊ����Ҫ��father����
			if (grandChildR)
				grandChildR->_parent = father;

			//����balance factor
			father->_bf = child->_bf = 0;
		}

		//����
		void _RotateL(Node* child)
		{
			Node* father = child->_parent;
			Node* grandChildL = child->_left;
			Node* grandFather = father->_parent;

			child->_parent = grandFather;

			//���grandFather��Ϊ����Ҫ��child����
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

			//���grandChildL��Ϊ����Ҫ��father����
			if (grandChildL)
				grandChildL->_parent = father;

			//����balance factor
			father->_bf = child->_bf = 0;
		}

		//����˫��
		void _RotateLR(Node* child)
		{
			Node* father = child->_parent;
			Node* grandChildR = child->_right;
			
			int bf = grandChildR->_bf;
			//��������
			_RotateL(grandChildR);
			//�ҵ�������
			_RotateR(grandChildR);

			//����balace factor
			if (bf == -1)
				father->_bf = 1;
			else if (bf == 1)
				child->_bf = -1;
		}

		//����˫��
		void _RotateRL(Node* child)
		{
			Node* father = child->_parent;
			Node* grandChildL = child->_left;
			int bf = grandChildL->_bf;

			//�ҵ�������
			_RotateR(grandChildL);
			//��������
			_RotateL(grandChildL);

			//����balance factor
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

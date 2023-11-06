#include <iostream>
#include <stack>

using namespace std;
//3.��Ӽ�������һ����������:a1,a2,a3.. an�����㷨ʵ��:��ջ�ṹ�洢�������������ai��-1ʱ����ai��ջ; 
// ��a=-1ʱ�����ջ����������ջ���㷨Ӧ���쳣���(��ջ����)������Ӧ����Ϣ��

//˳��ջ
class stack {
#define MAXSIZE 10
public:
	stack()
		:_base(new int[MAXSIZE])
		,_top(_base)
		,_stacksize(MAXSIZE)
	{}
	~stack()
	{
		delete[] _base;
		_base = _top = nullptr;
		_stacksize = 0;
	}
	void store(int* a)
	{
		for (int i = 0; i < _top - _base; i++)
		{
			if (_top == _base + _stacksize)
			{
				cout << "ջ����" << endl;
			}
			if (a[i] == -1)
			{
				if (!empty())
				{
					pop(a[i]);

				}
				else
				{
					cout << "ջ�ѿ�" << endl;
				}
			}
			else
			{
				push(a[i]);
			}
		}
	}

private:
	bool empty()
	{
		if (_base == _top)
		{
			return true;
		}
		return false;
	}
	int pop(int n)
	{
		if (!empty())
		{
			_top--;
		}
		return *_top;
	}
	void push(int n)
	{
		*_top = n;
		_top++;
	}
	
private:
	int* _base;
	int* _top;
	int _stacksize;
};

//6.�����Դ�ͷ����ѭ�������ʾ���У�����ֻ��һ��ָ��ָ���βԪ�ؽ��(ע��:��
// ��ͷָ��)���Ա�д��Ӧ���ÿն��С��ж϶����Ƿ�Ϊ�ա���Ӻͳ��ӵ��㷨��
class list {
	list()
		:_front(new listnode[1])
		,_rear(_front)
	{
		//��ͷѭ�������ͷ�ڵ�
		_front->_data = 0;
		_front->next = _front;
	}
	bool empty()
	{
		if (_front == _rear)
			return true;
		return false;
	}
	int pop()
	{
		if (!empty())
		{
			listnode* tmp = _front->next;
			_front->next = tmp->next;
			int ret = tmp->_data;
			delete[] tmp;
			tmp = nullptr;
			return ret;
		}
		else
		{
			cout << "�����ѿ�" << endl;
		}
	}
	void push(int n)
	{
		listnode* tmp = new listnode[1];
		tmp->_data = n;
		tmp->next = _front;
		_rear->next = tmp;
	}
	list& set_empty()
	{
		while (_front != _rear)
		{
			pop();
		}
		return *this;
	}
	int get_head()
	{
		if (!empty())
		{
			return _front->next->_data;
		}
	}
	~list()
	{
		set_empty();
		delete[] _front;
		_front = nullptr;
		_rear = nullptr;
	}
private:
	class listnode{
	public:
		int _data;
		listnode* next;
	};
	listnode* _front;
	listnode* _rear;
};



#include <iostream>

using namespace std;


//(2)�������ǵݼ�����������ϲ�Ϊһ���ǵ�������������
// Ҫ����������ʹ��ԭ����������Ĵ洢�ռ䣬������ռ�������Ĵ洢�ռ䡣�����������ظ������ݡ�
class ListNode {
public:
	ListNode* merge_list(ListNode* l1, ListNode* l2)
	{
		ListNode* p = nullptr;
		//�ǵ�������ͷ�ڵ㣬���Ҵ�
		if (l1->val <= l2->val)
		{
			p = l2;
			l2 = l2->next;
		}
		else
		{
			p = l1;
			l1 = l1->next;
		}
		while (l1 && l2)
		{
			if (l1->val <= l2->val)
			{
				p->next = l2;
				l2 = l2->next;
			}
			else
			{
				p->next = l1;
				l1 = l1->next;
			}
		}
		if (l1)
		{
			p->next = l1;
		}
		else
		{
			p->next = l2;
		}
		return p;
	}

	//(4)��֪��������A��B�ֱ��ʾ�������ϣ����ص������С�������㷨�����������A��B�Ĳ
	// (��������A�г��ֶ����� B �г��ֵ��������ɵļ���)��
	// ����ͬ������ʽ�洢ͬʱ���ظü��ϵ�Ԫ�ظ�����
	ListNode* diffrence_list(ListNode* l1, ListNode* l2)
	{
		//l1,l2�Ǵ�ͷ�ڵ������
		ListNode* head = l1;
		ListNode* pre = l1;
		l1 = l1->next;
		l2 = l2->next;
		while (l1 && l2)
		{
			if (l1->val == l2->val)
			{
				pre->next = l1 ->next;
				delete l1;
				l1 = pre->next;
			}
			else if (l1->val > l2->val)
			{
				l2 = l2->next;
			}
			else
			{
				pre = l1;
				l1 = l1->next;
			}
		}
		return head;
	}

	//(6)���һ���㷨��ͨ��һ�˱���ȷ������Ϊn�ĵ�������ֵ���Ľ�㡣
	ListNode* max_node(ListNode* l1)
	{
		ListNode* max = l1;
		while (l1)
		{
			if (l1->val > max->val)
			{
				max = l1;
			}
			l1 = l1->next;
		}
		return max;
	}


private:
	int val;
	ListNode* next;
};






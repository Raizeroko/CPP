#include "List.h"


// MySolution
class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        int Alength = 0;
        int Blength = 0;
        ListNode* curA = headA;
        ListNode* curB = headB;
        while (curA)
        {
            curA = curA->next;
            Alength++;
        }
        while (curB)
        {
            curB = curB->next;
            Blength++;
        }
        int k = Alength - Blength;

        curA = headA;
        curB = headB;
        if (k > 0)
        {
            while (k != 0)
            {
                curA = curA->next;
                k--;
            }
        }
        else
        {
            while (k != 0)
            {
                curB = curB->next;
                k++;
            }
        }

        while (curA != curB && curA && curB)
        {
            curA = curA->next;
            curB = curB->next;
        }
        if (curA == curB)
        {

            return curA;
        }
        return nullptr;
    }
};


//OptimSolution
class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        ListNode* curA = headA;
        ListNode* curB = headB;

        // ����ָ��ͬʱ��������ָ���ߵ�β��ʱ�л�����һ������
        while (curA != curB) {
            curA = (curA == nullptr) ? headB : curA->next;
            curB = (curB == nullptr) ? headA : curB->next;
        }

        return curA; // ����ཻ�����ؽ��㣻���򷵻� nullptr
    }
};
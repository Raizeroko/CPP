#include "List.h"

//MySolution
class Solution {
public:
    // �����������нڵ㰴���д洢����żֵ�ֿ��������ӣ�������������ĵ�һλ��ż��������ż����㶼������ǰ�棬
    // ���������������������ǰ��
    ListNode* oddEvenList1(ListNode* head) {
        if (!head) {
            return head;
        }
        int flag = head->val % 2;
        ListNode* fasthead = head;
        ListNode* fastcur = fasthead;
        ListNode* slowhead = nullptr;
        ListNode* slowcur = nullptr;
        ListNode* cur = fasthead->next;
        while (cur) {
            if (cur->val % 2 == flag) {
                fastcur->next = cur;
                fastcur = cur;
            }
            else {
                if (!slowhead) {
                    slowhead = cur;
                    slowcur = slowhead;
                }
                else {
                    slowcur->next = cur;
                    slowcur = cur;
                }
            }
            cur = cur->next;
        }
        slowcur->next = nullptr;
        fastcur->next = slowhead;
        return fasthead;
    }

    // ��������㣨�ǽ��洢����żֵ����ǰ��ż����ں�
    ListNode* oddEvenList(ListNode* head) {
        if (!head) {
            return head;
        }
        int flag = 0;
        ListNode* fasthead = head;
        ListNode* fastcur = fasthead;
        ListNode* slowhead = nullptr;
        ListNode* slowcur = nullptr;
        ListNode* cur = fasthead->next;
        while (cur) {
            if (flag % 2 == 1) {
                fastcur->next = cur;
                fastcur = cur;
            }
            else {
                if (!slowhead) {
                    slowhead = cur;
                    slowcur = slowhead;

                }
                else {
                    slowcur->next = cur;
                    slowcur = cur;
                }
            }
            cur = cur->next;
            flag++;
        }
        if (slowcur) {
            slowcur->next = nullptr;
        }
        fastcur->next = slowhead;
        return fasthead;
    }

};
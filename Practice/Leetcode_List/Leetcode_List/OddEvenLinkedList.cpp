#include "List.h"

//MySolution
class Solution {
public:
    // 将链表内所有节点按其中存储的奇偶值分开重新链接，并且输入链表的第一位是偶数那所有偶数结点都排在最前面，
    // 否则所有奇数结点排在最前面
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

    // 链表的奇结点（非结点存储的奇偶值）在前，偶结点在后
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
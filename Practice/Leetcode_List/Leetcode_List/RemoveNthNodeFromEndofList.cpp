#include "List.h"

// MySolution
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int num = 0;
        ListNode* cur = head;
        while (cur)
        {
            cur = cur->next;
            num++;
        }
        if (num == n)
            return head->next;
        cur = head;
        num -= n;
        ListNode* prev = nullptr;
        while (num)
        {
            prev = cur;
            cur = cur->next;
            num--;
        }
        prev->next = cur->next;
        delete cur;
        return head;
    }
};


// OptimSolution
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* cur = head;
        while (n--) {
            cur = cur->next;
        }
        if (!cur) {
            return head->next;
        }
        ListNode* prev = head;
        while (cur->next) {
            prev = prev->next;
            cur = cur->next;
        }
        ListNode* tmp = prev->next;
        prev->next = prev->next->next;
        delete tmp;
        return head;
    }
};


// Remove 2025/03/09
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int num = 0;
        ListNode* tmp = head;
        while (tmp) {
            tmp = tmp->next;
            num++;
        }
        int k = 0;
        ListNode* prev = nullptr;
        ListNode* cur = head;
        while (k < num - n) {
            prev = cur;
            cur = cur->next;
            k++;
        }
        if (!prev) {
            return head->next;
        }
        prev->next = cur->next;
        delete cur;
        return head;
    }
};
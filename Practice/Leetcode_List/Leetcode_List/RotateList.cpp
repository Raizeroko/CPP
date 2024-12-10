#include "List.h"

// MySolution
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        deque<int> dq;
        ListNode* cur = head;
        int num = 0;
        if (!head) {
            return head;
        }
        while (cur) {
            dq.push_back(cur->val);
            cur = cur->next;
            num++;
        }
        k = k % num;
        while (k--) {
            int back = dq.back();
            dq.pop_back();
            dq.push_front(back);
        }
        ListNode* tmp = head;
        while (tmp) {
            tmp->val = dq.front();
            cout << tmp->val;
            dq.pop_front();
            tmp = tmp->next;
        }
        return head;
    }
};

// OptimSolution
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head) {
            return head;
        }
        ListNode* tail = head;
        int num = 1;
        while (tail->next) {
            tail = tail->next;
            num++;
        }
        tail->next = head;
        k = k % num;
        num -= k;
        ListNode* prev = nullptr;
        ListNode* cur = head;
        while (num) {
            prev = cur;
            cur = cur->next;
            num--;
        }
        prev->next = nullptr;
        return cur;
    }
};
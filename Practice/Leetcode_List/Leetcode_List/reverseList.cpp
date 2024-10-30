#include "List.h"

// MySolution
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* next = head;
        ListNode* cur = nullptr;
        while (next)
        {
            ListNode* tmp = next->next;
            next->next = cur;
            cur = next;
            next = tmp;
        }
        return cur;
    }
};

// RecursionSolution
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;
        ListNode* next = head->next;
        ListNode* newhead = reverseList(next);
        next->next = head;
        head->next = nullptr;
        return newhead;
    }
};
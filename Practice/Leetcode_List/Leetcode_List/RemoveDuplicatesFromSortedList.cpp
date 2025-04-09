#include "List.h"

// MySolution
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode* fast = head->next;
        ListNode* slow = head;

        while (fast) {
            if (fast->val == slow->val) {
                ListNode* tmp = fast;
                fast = fast->next;
                slow->next = fast;
                delete tmp;
            }
            else {
                slow = fast;
                fast = fast->next;
            }
        }
        return head;
    }
};


// Review 2025/04/09
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head) return head;
        ListNode* cur = head->next;
        ListNode* prev = head;
        while (cur) {
            if (cur->val == prev->val) {
                prev->next = cur->next;
                delete cur;
                cur = prev->next;
            }
            else {
                prev = prev->next;
                cur = cur->next;
            }
        }
        return head;
    }
};
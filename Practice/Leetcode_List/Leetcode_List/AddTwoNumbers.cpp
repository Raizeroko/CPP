#include "List.h"

// MySolution
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* cur1 = l1;
        ListNode* cur2 = l2;
        ListNode* prev = nullptr;
        int carry = 0;
        while (cur1 && cur2) {
            int tmp = cur1->val + cur2->val + carry;
            cur1->val = tmp % 10;
            carry = tmp / 10;
            prev = cur1;
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        // 如果不是cur2走到最后
        if (cur2) {
            prev->next = cur2;
        }
        ListNode* back = prev->next;
        while (carry && back) {
            int tmp = back->val + carry;
            back->val = tmp % 10;
            carry = tmp / 10;
            prev = back;
            back = back->next;
        }
        if (carry) {
            prev->next = new ListNode(carry);
        }
        return l1;
    }
};
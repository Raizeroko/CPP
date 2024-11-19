#include "List.h"

// MySolution
class Solution {
public:
    ListNode* reverseList(ListNode* cur) {
        ListNode* prev = nullptr;
        printf("%d", cur->val);
        while (cur) {
            ListNode* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }


    bool isPalindrome(ListNode* head) {
        int num = 0;
        ListNode* cur = head;
        while (cur) {
            cur = cur->next;
            num++;
        }
        if (num == 1) {
            return true;
        }
        int half = num / 2;
        if (num % 2 == 1) {
            half += 1;
        }
        ListNode* fast = head;
        while (half--) {
            fast = fast->next;
        }
        ListNode* rev = reverseList(fast);
        ListNode* slow = head;
        while (rev) {
            if (rev->val != slow->val) {
                return false;
            }
            rev = rev->next;
            slow = slow->next;
        }
        return true;
    }
};
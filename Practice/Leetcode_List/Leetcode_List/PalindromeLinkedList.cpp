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


// Review 2025_03_08
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast) {
            slow = slow->next;
            fast = fast->next;
            if (!fast) break;
            fast = fast->next;
        }
        if (!slow) return true;
        // 逆转链表后半部分
        ListNode* mid = slow;
        ListNode* next = mid->next;
        mid->next = nullptr;
        while (next) {
            ListNode* tmp = next->next;
            next->next = mid;
            mid = next;
            next = tmp;
        }
        ListNode* cur = head;
        while (mid) {
            if (cur->val != mid->val) {
                return false;
            }
            mid = mid->next;
            cur = cur->next;
        }
        return true;
    }
};
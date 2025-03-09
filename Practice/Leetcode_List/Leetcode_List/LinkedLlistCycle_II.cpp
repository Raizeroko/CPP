#include "List.h"

// MySolution
class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast != nullptr) {
            fast = fast->next;
            if (!fast) break;
            fast = fast->next;
            slow = slow->next;
            if (fast == slow) {
                slow = head;
                while (slow != fast) {
                    slow = slow->next;
                    fast = fast->next;
                }
                return fast;
            }
        }
        return nullptr;
    }
};

// Review 2025_03_09
class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != nullptr) {
            fast = fast->next;
            if (!fast)   break;
            slow = slow->next;
            fast = fast->next;
            if (fast == slow) {
                fast = head;
                while (fast != slow) {
                    fast = fast->next;
                    slow = slow->next;
                }
                return slow;
            }
        }
        return nullptr;
    }
};
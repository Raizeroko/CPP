#include "list.h"

// MySolution
class Solution {
public:
    bool hasCycle(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast != nullptr) {
            fast = fast->next;
            if (!fast) break;
            fast = fast->next;
            slow = slow->next;
            if (fast == slow) {
                return true;
            }
        }
        return false;
    }
};

// Review 2025_03_08
class Solution {
public:
    bool hasCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast) {
            slow = slow->next;
            fast = fast->next;
            if (!fast) return false;
            fast = fast->next;
            if (slow == fast) return true;
        }
        return false;
    }
};
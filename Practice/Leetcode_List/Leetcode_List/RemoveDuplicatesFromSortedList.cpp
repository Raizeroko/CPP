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

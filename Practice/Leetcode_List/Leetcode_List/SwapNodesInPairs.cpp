#include "List.h"

// MySolution
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }
        ListNode* prev = nullptr;
        ListNode* cur = head;
        head = cur->next;
        while (cur && cur->next) {
            ListNode* next = cur->next;
            cur->next = next->next;
            next->next = cur;
            if (prev) {
                prev->next = next;
            }
            prev = cur;
            cur = cur->next;
        }
        return head;
    }
};


//
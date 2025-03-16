#include "List.h"

// MySolution
class Solution {
public:
    ListNode* reverse(stack<ListNode*>& s) {
        ListNode* r_head = s.top();
        ListNode* tail = r_head->next;
        ListNode* cur = r_head;
        s.pop();
        while (!s.empty()) {
            ListNode* next = s.top();
            s.pop();
            cur->next = next;
            cur = cur->next;
        }
        cur->next = tail;
        return cur;
    }


    ListNode* reverseKGroup(ListNode* head, int k) {
        stack<ListNode*> s;
        ListNode* cur = head;
        ListNode* ret_head = nullptr;
        ListNode* before_tail = nullptr;
        while (cur || s.size() == k) {
            if (s.size() != k) {
                s.push(cur);
                cur = cur->next;
            }
            else {
                // Äæ×ª[n,n+k]
                ListNode* r_head = s.top();
                ListNode* r_tail = reverse(s);
                if (ret_head == nullptr) {
                    ret_head = r_head;
                }
                else {
                    before_tail->next = r_head;
                }
                before_tail = r_tail;
            }

        }
        return ret_head;
    }
};
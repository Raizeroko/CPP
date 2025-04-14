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


// Review 2025/04/14
class Solution {
public:
    void Reverse(ListNode* start, ListNode* end) {
        ListNode* prev = nullptr;
        ListNode* cur = start;
        while (cur != end) {
            ListNode* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* prev_head = new ListNode(0);
        prev_head->next = head;
        ListNode* start = head;
        ListNode* prev = prev_head;
        while (start) {
            ListNode* end = start;
            for (int i = 1; i < k; i++) {
                end = end->next;
                if (!end) {
                    return prev_head->next;
                }
            }
            ListNode* next = end->next;
            Reverse(start, end->next);
            prev->next = end;
            start->next = next;
            prev = start;
            start = next;
        }
        return prev_head->next;
    }
};
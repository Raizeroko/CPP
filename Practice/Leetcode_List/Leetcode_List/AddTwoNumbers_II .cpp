#include "List.h"

//MySolution
class Solution2 {
public:

    int add(ListNode* l1, ListNode* l2) {
        if (!l1) {
            return 0;
        }
        int ret = l1->val + l2->val + add(l1->next, l2->next);
        l1->val = ret % 10;
        return ret / 10;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int num1 = 0;
        int num2 = 0;
        ListNode* cur1 = l1;
        ListNode* cur2 = l2;
        while (cur1) {
            cur1 = cur1->next;
            num1++;
        }
        while (cur2) {
            cur2 = cur2->next;
            num2++;
        }
        int diff = num1 - num2;
        if (num1 < num2) {
            diff = num2 - num1;
            swap(l1, l2);
        }
        cur1 = l1;
        cur2 = l2;
        ListNode* head = new ListNode;
        ListNode* cur = head;
        while (diff) {
            cur->next = new ListNode;
            cur = cur->next;
            diff--;
        }
        cur->next = l2;
        head->val += add(head->next, cur1);
        if (!head->val) {
            return head->next;
        }
        return head;
    }
};


//OptimSolution
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<ListNode*>* s1 = ListToStack(l1);
        stack<ListNode*>* s2 = ListToStack(l2);
        // 保证s1始终大于s2
        if (s2->size() > s1->size()) {
            swap(s1, s2);
        }
        int carry = 0;
        ListNode* cur1 = nullptr;
        while (!s2->empty()) {
            cur1 = s1->top();
            ListNode* cur2 = s2->top();
            s1->pop();
            s2->pop();
            cur1->val = cur1->val + cur2->val + carry;
            carry = 0;
            if (cur1->val >= 10) {
                carry = 1;
                cur1->val = cur1->val % 10;
            }
        }
        while (!s1->empty()) {
            cur1 = s1->top();
            s1->pop();
            cur1->val += carry;
            carry = 0;
            if (cur1->val >= 10) {
                carry = 1;
                cur1->val = cur1->val % 10;
            }
        }
        if (carry == 1) {
            ListNode* head = new ListNode(carry, cur1);
            return head;
        }
        return cur1;
    }
    stack<ListNode*>* ListToStack(ListNode* list) {
        stack<ListNode*>* s = new stack<ListNode*>;
        while (list) {
            s->push(list);
            list = list->next;
        }
        return s;
    }
};

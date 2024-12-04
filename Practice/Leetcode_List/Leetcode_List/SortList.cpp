#include "List.h"

// MySolution
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        vector<int> v;
        ListNode* cur = head;
        // תΪvector�洢
        while (cur != nullptr) {
            v.push_back(cur->val);
            cur = cur->next;
        }
        sort(v.begin(), v.end());
        cur = head;
        for (auto& e : v) {
            cur->val = e;
            cur = cur->next;
        }
        return head;
    }
};

// OptimSolution
class Solution {
public:
    ListNode* mergeSortedLists(ListNode* head1, ListNode* head2) {
        if (head1->val > head2->val) {
            swap(head1, head2);
        }
        ListNode* cur1 = head1;
        ListNode* cur2 = head2;
        while (cur2) {
            if (cur1->next == nullptr || cur1->next->val > cur2->val)
            {
                ListNode* tmp = cur2->next;
                cur2->next = cur1->next;
                cur1->next = cur2;
                cur2 = tmp;
            }
            else {
                cur1 = cur1->next;
            }

        }
        return head1;
    }


    ListNode* _sortList(ListNode* left, ListNode* right) {
        if (!left) {
            return left;
        }
        if (left->next == right) {
            return left;
        }
        ListNode* mid = left;
        ListNode* fast = left;
        while (fast != right) {
            fast = fast->next;
            if (fast == right) {
                break;
            }
            fast = fast->next;
            if (fast == right) {
                break;
            }
            mid = mid->next;
        }
        ListNode* tmp = mid;
        mid = mid->next;
        tmp->next = nullptr;
        ListNode* sort_left = _sortList(left, nullptr);
        ListNode* sort_right = _sortList(mid, right);
        return mergeSortedLists(sort_left, sort_right);
    }


public:
    ListNode* sortList(ListNode* head) {
        ListNode* ret = _sortList(head, nullptr);
        return ret;
    }
};
#include "List.h"


// MySolution
class Solution {
public:
        ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
            ListNode* cur1 = list1;
            ListNode* cur2 = list2;
            if (!cur1 || !cur2)
            {
                return cur1 ? cur1 : cur2;
            }
            if (cur2->val < cur1->val)
                swap(cur1, cur2);
            ListNode* ret = cur1;
            while (cur2)
            {
                if (cur1->next == nullptr || cur1->next->val > cur2->val)
                {
                    ListNode* tmp = cur2->next;
                    cur2->next = cur1->next;
                    cur1->next = cur2;
                    cur2 = tmp;
                }
                else
                {
                    cur1 = cur1->next;
                }
            }
            return ret;
        }
};


//RecursionSolution
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1 == nullptr) return list2;
        if (list2 == nullptr) return list1;
        if (list1->val < list2->val)
        {
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        }
        else
        {
            list2->next = mergeTwoLists(list1, list2->next);
            return list2;
        }
    }
};
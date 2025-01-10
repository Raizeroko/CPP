#include "List.h"

// MySolution
class Solution {
public:
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        ListNode* cur = head;
        while (cur->next) {
            ListNode* next = cur->next;
            auto commonDivisor = [](int a, int b) {
                while (b != 0) {
                    int tmp = b;
                    b = a % b;
                    a = tmp;
                }
                return a;
                };
            ListNode* cd = new ListNode(commonDivisor(cur->val, next->val));
            cur->next = cd;
            cd->next = next;
            cur = next;
            next = cur->next;
        }
        return head;
    }
};
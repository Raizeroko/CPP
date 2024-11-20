#include "List.h"

// MySolution
class Solution {
public:
    ListNode* splitList(ListNode*& cur, int split) {
        ListNode* ret = cur;
        ListNode* prev = nullptr;
        while (split) {
            prev = cur;
            cur = cur->next;
            split--;
        }
        prev->next = nullptr;
        return ret;
    }

    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        // 获取链表总长度
        int num = 0;
        ListNode* cur = head;
        while (cur) {
            cur = cur->next;
            num++;
        }
        vector<ListNode*> ret(k, nullptr);
        cur = head;
        int split = 1;
        int remain = 0;
        if (num > k) {
            split = num / k;
            remain = num % k;
        }
        for (int i = 0; cur && i < k; i++) {
            if (remain > 0) {
                remain--;
                ret[i] = splitList(cur, split + 1);
            }
            else {
                ret[i] = splitList(cur, split);
            }
        }
        return ret;
    }
};
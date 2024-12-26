#include "harsh.h"

// MySolution
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> set(nums.begin(), nums.end());
        int ret = 0;
        for (auto value : set) {
            if (!set.count(value - 1)) {
                int length = 1;
                while (set.count(value + 1)) {
                    length++;
                    value++;
                }
                ret = max(ret, length);
            }

        }
        return ret;
    }
};
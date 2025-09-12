#include "Vector.h"

// MySolution
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int maxlen = 0;
        for (int l = 0, r = 0, tmp = 0; r < nums.size(); r++) {
            if (nums[r] == 0) tmp++;

            while (tmp > k) {
                if (nums[l++] == 0) tmp--;
            }
            maxlen = max(maxlen, r - l + 1);
        }
        return maxlen;
    }
};
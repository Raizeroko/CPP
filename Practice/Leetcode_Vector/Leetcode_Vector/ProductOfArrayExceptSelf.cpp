#include "Vector.h"

// MySolution
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        int lp = 1, rp = 1;
        vector<int> ret(nums.size(), 1);
        while (l < nums.size() && r >= 0) {
            ret[l] *= lp;
            ret[r] *= rp;
            lp *= nums[l++];
            rp *= nums[r--];
        }
        return ret;
    }
};
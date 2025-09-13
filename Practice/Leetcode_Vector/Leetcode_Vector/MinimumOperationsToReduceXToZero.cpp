#include "Vector.h"

// MySolution
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int sum = 0;
        for (auto num : nums) {
            sum += num;
        }
        int target = sum - x;
        if (target < 0) return -1;
        if (target == 0) return nums.size();
        int l = 0;
        int r = 0;
        int ret = 0;
        int cur = 0;
        while (r < nums.size()) {
            cur += nums[r];
            while (cur > target) {
                cur -= nums[l];
                l++;
            }
            if (cur == target) ret = max(ret, r - l + 1);
            r++;
        }
        if (ret == 0) return -1;
        return nums.size() - ret;


    }
};
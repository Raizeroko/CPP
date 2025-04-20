#include "Puzzle.h"

// MySolution
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0;
        int r = nums.size() - 1;
        int ret = nums[0];
        while (l <= r) {
            int mid = l + (r - l) / 2;
            // min = min(min, nums[mid]);
            if (nums[mid] >= nums[l]) {
                // 左半部分都是递增
                ret = min(ret, nums[l]);
                l = mid + 1;
            }
            else {
                ret = min(ret, nums[mid]);
                r = mid - 1;
            }
        }
        return ret;
    }
};
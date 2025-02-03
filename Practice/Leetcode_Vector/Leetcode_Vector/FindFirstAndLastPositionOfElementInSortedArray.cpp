#include "Vector.h"

// MySolution
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int start = 0;
        int end = nums.size() - 1;
        while (start < nums.size() && nums[start] != target) {
            start++;
        }
        vector<int> ret;
        ret.push_back(start == nums.size() ? -1 : start);
        while (end >= 0 && nums[end] != target) {
            end--;
        }
        ret.push_back(end == -1 ? -1 : end);
        return ret;
    }
};
#include "Vector.h"

// MySolution
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int slow = 0;
        int fast = 0;
        while (fast < nums.size()) {
            if (nums[fast]) {
                swap(nums[fast], nums[slow]);
                slow++;
            }
            fast++;
        }
    }
};
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


// Review 2025/09/10
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int dist = -1;
        for (int cur = 0; cur < nums.size(); cur++) {
            if (nums[cur] != 0) {
                swap(nums[++dist], nums[cur]);
            }
        }
    }
};








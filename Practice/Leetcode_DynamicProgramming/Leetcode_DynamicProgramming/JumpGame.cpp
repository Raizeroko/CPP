#include "DP.h"


// MySolution
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int jump = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (i <= jump) {
                jump = max(jump, i + nums[i]);
                if (jump >= nums.size() - 1) {
                    return true;
                }
            }
        }
        return false;
    }
};
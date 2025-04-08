#include "Puzzle.h"

// MySolution
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];
    }
};

// OptimSolution
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int cur = nums[0];
        int times = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == cur) times++;
            else {
                times--;
                if (times < 0) {
                    cur = nums[i];
                    times = 1;
                }
            }
        }
        return cur;
    }
};

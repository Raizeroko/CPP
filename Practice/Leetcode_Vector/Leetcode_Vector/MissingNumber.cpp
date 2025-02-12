#include "Vector.h"

// MySolution
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        unordered_set<int> harsh;
        for (auto& num : nums) {
            harsh.insert(num);
        }
        int ret = -1;
        for (int i = 0; i < nums.size() + 1; i++) {
            if (harsh.find(i) == harsh.end()) {
                ret = i;
                break;
            }
        }
        return ret;
    }
};

// MySolution
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (nums[i] != i) {
                return i;
            }
        }
        return n;
    }
};


// OptimSolution
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        return ((1 + nums.size()) * nums.size() / 2) - accumulate(nums.begin(), nums.end(), 0);
    }
};
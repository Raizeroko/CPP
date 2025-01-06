#include "Vector.h"


// MySolution
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> ret(nums.size());
        for (int i = 0; i < ret.size(); i++) {
            ret[i] = i + 1;
        }
        for (int i = 0; i < nums.size(); i++) {
            ret[nums[i] - 1] = 0;
        }
        auto it = ret.begin();
        while (it != ret.end()) {
            if (*it == 0) {
                it = ret.erase(it);
            }
            else {
                it++;
            }
        }
        return ret;
    }
};

// OptimSolution
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        for (auto& num : nums) {
            int k = (num - 1) % nums.size();
            if (nums[k] <= nums.size())
                nums[k] += nums.size();
        }
        vector<int> ret;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] <= nums.size()) {
                ret.push_back(i + 1);
            }
        }

        return ret;
    }
};
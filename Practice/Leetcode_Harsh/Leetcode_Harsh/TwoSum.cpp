#include "harsh.h"

// MySolution
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> harsh;
        vector<int> v;
        for (int i = 0; i < nums.size(); i++) {
            auto it = harsh.find(target - nums[i]);
            if (it != harsh.end()) {
                v.push_back(it->second);
                v.push_back(i);
                break;
            }
            else {
                harsh[nums[i]] = i;
            }
        }
        return v;
    }
};
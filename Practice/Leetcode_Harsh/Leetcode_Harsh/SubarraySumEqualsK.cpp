#include "harsh.h"

// MySolution
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> prefixSumCount;
        prefixSumCount[0] = 1;

        int ret = 0, currentSum = 0;

        for (int num : nums) {
            currentSum += num;
            if (prefixSumCount.find(currentSum - k) != prefixSumCount.end()) {
                ret += prefixSumCount[currentSum - k];
            }

            prefixSumCount[currentSum]++;
        }

        return ret;
    }
};
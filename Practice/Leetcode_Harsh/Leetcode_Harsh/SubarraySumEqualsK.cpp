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

// Review 2025_03_06
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        // key: beforeSum
        unordered_map<int, int> harsh;
        // 初始前和为0的个数为1
        int beforeSum = 0;
        harsh[beforeSum] = 1;
        int ret = 0;
        for (auto num : nums) {
            beforeSum += num;
            if (harsh.count(beforeSum - k)) {
                ret += harsh[beforeSum - k];
            }
            harsh[beforeSum]++;
        }
        return ret;
    }
};



// Review 2025/05/06
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        // 前缀和各值的个数
        unordered_map<int, int> harsh;
        int sum = 0;
        int ret = 0;
        // 默认存在前缀和为0的前缀和个数为1
        harsh[0] = 1;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            if (harsh.count(sum - k)) ret += harsh[sum - k];
            // 前缀和每个都要加入哈希表中
            harsh[sum]++;
        }
        return ret;
    }
};
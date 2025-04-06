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
        // ��ʼǰ��Ϊ0�ĸ���Ϊ1
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
        // ǰ׺�͸�ֵ�ĸ���
        unordered_map<int, int> harsh;
        int sum = 0;
        int ret = 0;
        // Ĭ�ϴ���ǰ׺��Ϊ0��ǰ׺�͸���Ϊ1
        harsh[0] = 1;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            if (harsh.count(sum - k)) ret += harsh[sum - k];
            // ǰ׺��ÿ����Ҫ�����ϣ����
            harsh[sum]++;
        }
        return ret;
    }
};
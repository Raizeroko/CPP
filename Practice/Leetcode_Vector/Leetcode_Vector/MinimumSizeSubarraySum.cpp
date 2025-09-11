#include "Vector.h"

// MySolution
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        queue<int> q;
        int tmp = 0;
        int ret = nums.size() + 1;
        int i = 0;
        for (int i = 0; i < nums.size(); i++) {
            tmp += nums[i];
            q.push(nums[i]);
            while (!q.empty() && tmp >= target) {
                if (q.size() < ret) {
                    ret = q.size();
                }
                tmp -= q.front();
                q.pop();
            }
        }
        while (tmp >= target) {
            tmp -= q.front();
            q.pop();
            if (q.size() <= ret) {
                ret = q.size();
            }
        }
        if (ret == nums.size() + 1) {
            return 0;
        }
        return ret;
    }
};

// Review 2025/09/11
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int left = 0;
        int right = 0;
        int ret = nums.size() + 1;
        int sum = 0;
        while (right < nums.size()) {
            sum += nums[right];
            while (sum >= target) {
                ret = min(ret, right - left + 1);
                sum -= nums[left];
                left++;
            }
            right++;
        }
        return ret == nums.size() + 1 ? 0 : ret;
    }
};
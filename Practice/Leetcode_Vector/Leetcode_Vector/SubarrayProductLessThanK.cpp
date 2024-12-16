#include <vector>

using namespace std;

// MySolution
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int ans = 0;
        int length = nums.size();
        for (int j = 0; j < length; j++) {
            int temp = 1;
            for (int i = j; i < length; i++) {
                temp *= nums[i];
                if (temp >= k) {
                    break;
                }
                ans++;
            }
        }
        return ans;
    }
};


// OptimSolution
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int length = nums.size();
        int left = 0;
        int mul = 1;
        int ret = 0;
        for (int right = 0; right < length; right++) {
            mul *= nums[right];
            while (left <= right && mul >= k) {
                mul /= nums[left];
                left++;
            }
            ret += right - left + 1;
        }
        return ret;
    }
};
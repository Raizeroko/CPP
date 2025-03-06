#include "Vector.h"

// MySolution
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ret;
        for (int i = 0; nums[i] <= 0 && i < nums.size() - 2; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            int target = -nums[i];
            int left = i + 1;
            int right = nums.size() - 1;
            while (left < right) {
                if (nums[left] + nums[right] == target) {
                    vector<int> tmp = { nums[i], nums[left], nums[right] };
                    ret.push_back(tmp);
                    left++;
                    right--;
                    while (left < right && nums[left] == nums[left - 1]) left++;
                    while (left < right && nums[right] == nums[right + 1]) right--;
                }
                else if (nums[left] + nums[right] < target) {
                    left++;
                }
                else {
                    right--;
                }
            }
        }
        return ret;
    }
};
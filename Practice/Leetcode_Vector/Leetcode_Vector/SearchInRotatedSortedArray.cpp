#include "Vector.h"

// MySolution
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int ret = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                ret = mid;
                break;
            }
            if (nums[mid] >= nums[left]) {
                // left��midС��������ϸ����
                if (target >= nums[left] && target <= nums[mid]) right = mid - 1;
                else left = mid + 1;

            }
            else {
                // �ұ����ϸ����
                if (nums[right] >= target && target >= nums[mid]) left = mid + 1;
                else right = mid - 1;
            }
        }
        return ret;
    }
};
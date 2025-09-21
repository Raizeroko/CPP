#include "Puzzle.h"

// MySolution
class Solution {
public:
    int BinarySearch(const vector<int>& nums, int target, bool is_left_bound) {
        // 数组为空
        if (nums.size() == 0) return -1;
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                if (is_left_bound == 0) left = mid + 1;
                else right = mid - 1;
            }
            else if (nums[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
        int ret = is_left_bound ? left : right;
        if (ret >= 0 && ret < nums.size() && nums[ret] == target) return ret;
        return -1;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> ret;
        // 以二分法解决
        // 左边界
        ret.push_back(BinarySearch(nums, target, true));
        // 右边界
        ret.push_back(BinarySearch(nums, target, false));
        return ret;
    }
};


// Review 2025/09/21
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size();
        if (n == 0) return { -1, -1 };
        int l = 0;
        int r = n - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] < target) l = mid + 1;
            else r = mid - 1;
        }
        int begin = l;
        if (begin >= n || nums[begin] != target) return { -1, -1 };
        l = 0;
        r = n - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] > target) r = mid - 1;
            else l = mid + 1;
        }
        int end = r;
        return { begin, end };

    }
};
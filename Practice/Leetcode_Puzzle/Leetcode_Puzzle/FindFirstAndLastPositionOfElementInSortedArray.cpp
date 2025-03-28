#include "Puzzle.h"

// MySolution
class Solution {
public:
    int BinarySearch(const vector<int>& nums, int target, bool is_left_bound) {
        // ����Ϊ��
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
        // �Զ��ַ����
        // ��߽�
        ret.push_back(BinarySearch(nums, target, true));
        // �ұ߽�
        ret.push_back(BinarySearch(nums, target, false));
        return ret;
    }
};
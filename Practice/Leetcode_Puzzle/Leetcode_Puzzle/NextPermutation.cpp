#include "Puzzle.h"

// MySolution(214/266)
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int r = nums.size() - 1;
        while (r > 0) {
            int l = r - 1;
            while (l >= 0) {
                if (nums[l] < nums[r]) {
                    swap(nums[r], nums[l]);
                    sort(nums.begin() + l + 1, nums.end());
                    return;
                }
                l--;
            }
            r--;
        }
        sort(nums.begin(), nums.end());
        return;
    }
};

// OptimSolution
class Solution {
public:
    void reverse(vector<int>& nums, int l, int r) {
        while (l < r) {
            swap(nums[l++], nums[r--]);
        }
    }

    void nextPermutation(vector<int>& nums) {
        int l = nums.size() - 1;
        while (--l >= 0) {
            if (nums[l] < nums[l + 1]) {
                break;
            }
        }
        if (l >= 0) {
            int r = nums.size() - 1;
            while (r > l) {
                if (nums[r] > nums[l]) {
                    swap(nums[r], nums[l]);
                    reverse(nums, l + 1, nums.size() - 1);
                    return;
                }
                r--;
            }
        }
        else {
            reverse(nums, 0, nums.size() - 1);
        }
    }
};
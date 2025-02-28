#include "Vector.h"

// MySolution
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int end = nums.size() - 1;
        int begin = 0;
        while (begin < end) {
            if (nums[begin] == val) {
                swap(nums[begin], nums[end]);
                end--;
            }
            else {
                begin++;
            }
        }
        auto rit = nums.rbegin();

        while (rit != nums.rend() && *rit == val) {
            rit++;
        }
        return nums.rend() - rit;

    }
};

// OptimSolution
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int end = nums.size();
        int begin = 0;
        while (begin < end) {
            if (nums[begin] == val) {
                swap(nums[begin], nums[end - 1]);
                end--;
            }
            else {
                begin++;
            }
        }
        return begin;

    }
};
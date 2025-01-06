#include "Vector.h"

// MySolution
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int color[3] = { 0, 0, 0 };
        for (auto& num : nums) {
            color[num]++;
        }
        for (auto& num : nums) {
            if (color[0] != 0) {
                num = 0;
                color[0]--;
            }
            else if (color[1] != 0) {
                num = 1;
                color[1]--;
            }
            else if (color[2] != 0) {
                num = 2;
                color[2]--;
            }
        }
    }
};

// OptimSolution
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int i = 0;
        int red = 0;
        int blue = nums.size() - 1;
        while (i <= blue) {
            while (i <= blue && nums[i] == 2) {
                swap(nums[i], nums[blue]);
                blue--;
            }
            if (nums[i] == 0) {
                swap(nums[i], nums[red]);
                red++;
            }
            i++;
        }
    }
};
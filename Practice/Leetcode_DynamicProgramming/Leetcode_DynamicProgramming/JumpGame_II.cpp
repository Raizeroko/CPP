#include <vector>

using namespace std;

// MySolution
class Solution {
public:
    int jump(vector<int>& nums) {
        vector<int> jumpnums(nums.size(), nums.size());
        jumpnums[0] = 0;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 1; i + j < nums.size() && j <= nums[i]; j++) {
                if (jumpnums[i] + 1 < jumpnums[i + j]) {
                    jumpnums[i + j] = jumpnums[i] + 1;
                }
            }
        }
        return jumpnums[nums.size() - 1];
    }
};

// OptimSolution
class Solution {
public:
    int jump(vector<int>& nums) {
        int step = 0;
        int i = nums.size() - 1;
        while (i != 0) {
            for (int j = 0; j < i; j++) {
                if (j + nums[j] >= i) {
                    step++;
                    i = j;
                    break;
                }
            }
        }
        return step;
    }
};
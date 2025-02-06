#include "Vector.h"

// MySolution
class Solution {
    vector<int> unique;
public:
    void _permuteUnique(vector<int>& nums, int idx, vector<int>& sequence, vector<vector<int>>& ret) {
        if (idx == nums.size()) {
            ret.push_back(sequence);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (unique[i] || (i > 0 && nums[i] == nums[i - 1] && !unique[i - 1])) {
                continue;
            }
            sequence.push_back(nums[i]);
            unique[i] = 1;
            _permuteUnique(nums, idx + 1, sequence, ret);
            unique[i] = 0;
            sequence.pop_back();
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> ret;
        vector<int> sequence;
        unique.resize(nums.size());
        sort(nums.begin(), nums.end());
        _permuteUnique(nums, 0, sequence, ret);
        return ret;
    }
};
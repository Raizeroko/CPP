#include "Puzzle.h"

// MySolution
class Solution {
    vector<vector<int>> ret;
public:
    void dfs(const vector<int>& nums, int level, vector<int> path) {
        if (level == nums.size()) {
            ret.push_back(path);
            return;
        }
        // ��ѡ��ǰλ��
        dfs(nums, level + 1, path);

        // ѡ��ǰλ��
        path.push_back(nums[level]);
        dfs(nums, level + 1, path);
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> path;
        dfs(nums, 0, path);
        return ret;
    }
};
#include "Puzzle.h"

// MySolution
class Solution {
    vector<vector<int>> ret;

public:
    void dfs(const vector<int>& candidates, int target, int level, vector<int> comb) {
        if (level >= candidates.size()) {
            return;
        }
        if (target < 0) {
            return;
        }
        if (target == 0) {
            ret.push_back(comb);
        }
        int num = candidates[level];
        int k = 0;

        while (target - k * num >= 0) {
            int less = target - k * num;
            vector<int> tmp = comb;
            tmp.insert(tmp.end(), k, num);
            if (less == 0) {
                ret.push_back(tmp);
                return;
            }
            dfs(candidates, target - k * num, level + 1, tmp);
            k++;
        }
        return;

    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        if (target == 0) {
            return ret;
        }
        vector<int> comb;
        int level = 0;
        dfs(candidates, target, level, comb);
        return ret;
    }
};


// OptimSolution
class Solution {
    vector<vector<int>> ret;

public:

    void dfs(vector<int>& candidates, int target, int level, vector<int> comb) {
        if (target == 0) {
            ret.push_back(comb);
            return;
        }
        for (int i = level; i < candidates.size(); i++) {
            if (target < candidates[i]) {
                continue;
            }
            comb.push_back(candidates[i]);
            dfs(candidates, target - candidates[i], i, comb);
            comb.pop_back();;
        }

    }


    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        int level = 0;
        vector<int> comb;
        dfs(candidates, target, level, comb);
        return ret;
    }
};
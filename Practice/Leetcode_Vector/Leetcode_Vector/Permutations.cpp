#include "Vector.h"

// MySolution
class Solution {
public:
    void dfs(vector<vector<int>>& ret, int level, vector<int> push, vector<int> get) {
        if (get.size() == 0) {
            ret.push_back(push);
            return;
        }
        for (int i = 0; i < get.size(); i++) {
            vector<int> new_push = push;
            new_push.push_back(get[i]);
            vector<int> new_get = get;
            new_get.erase(new_get.begin() + i);
            dfs(ret, level + 1, new_push, new_get);;
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ret;
        vector<int> push;
        dfs(ret, 0, push, nums);
        return ret;
    }
};


// OptimSolution
class Solution {
public:
    void dfs(vector<vector<int>>& ret, vector<int>& push, int level, int size) {
        if (level == size) {
            ret.push_back(push);
            return;
        }
        for (int i = level; i < size; i++) {
            swap(push[i], push[level]);
            dfs(ret, push, level + 1, size);
            swap(push[i], push[level]);
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ret;
        dfs(ret, nums, 0, nums.size());
        return ret;
    }
};


// Review 2025/03/27
class Solution {
    vector<vector<int>> ret;
public:
    void dfs(vector<int> nums, int level){
        if(level == nums.size()){
            ret.push_back(nums);
            return;
        }
        for(int i = level; i < nums.size(); i++){
            swap(nums[level], nums[i]);
            dfs(nums, level+1);
            swap(nums[level], nums[i]);
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        dfs(nums, 0);
        return ret;
    }
};
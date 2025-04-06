#include "Tree.h"

// MySolution
class Solution {
private:
    int ret = 0;
public:
    void hasPathSum(TreeNode* root, long targetSum) {
        if (!root) {
            return;
        }
        targetSum -= root->val;
        if (targetSum == 0) {
            ret++;
        }
        hasPathSum(root->left, targetSum);
        hasPathSum(root->right, targetSum);
        return;
    }

    int pathSum(TreeNode* root, int targetSum) {
        if (!root) {
            return 0;
        }
        hasPathSum(root, targetSum);
        pathSum(root->left, targetSum);
        pathSum(root->right, targetSum);
        return ret;
    }
};

// Review 2025/04/06
class Solution {
    int ret = 0;
public:
    void hasPathSum(TreeNode* root, long targetSum) {
        if (!root) return;
        targetSum -= root->val;
        if (targetSum == 0) {
            ret++;
        }
        hasPathSum(root->left, targetSum);
        hasPathSum(root->right, targetSum);
    }
    int pathSum(TreeNode* root, int targetSum) {
        if (!root) return 0;
        hasPathSum(root, targetSum);
        pathSum(root->left, targetSum);
        pathSum(root->right, targetSum);
        return ret;
    }
};

// OptimSolution
class Solution {
    unordered_map<long, long> prefix;
    int ret = 0;
public:
    void dfs(TreeNode* root, int targetSum, long sum) {
        if (!root) return;
        sum += root->val;
        if (prefix.count(sum - targetSum)) ret += prefix[sum - targetSum];
        prefix[sum]++;
        dfs(root->left, targetSum, sum);
        dfs(root->right, targetSum, sum);
        prefix[sum]--;
    }

    int pathSum(TreeNode* root, int targetSum) {
        prefix[0] = 1;
        dfs(root, targetSum, 0);
        return ret;
    }
};
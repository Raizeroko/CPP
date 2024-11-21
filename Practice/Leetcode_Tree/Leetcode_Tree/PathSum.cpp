#include "Tree.h"

// MySolution
class Solution {
public:
    bool pathSum(TreeNode* root, int sum, int targetSum) {
        if (!root) {
            return false;
        }
        sum += root->val;
        if (sum == targetSum && !root->left && !root->right) {
            return true;
        }
        return pathSum(root->left, sum, targetSum) || pathSum(root->right, sum, targetSum);
    }


    bool hasPathSum(TreeNode* root, int targetSum) {
        return pathSum(root, 0, targetSum);
    }
};


// OptimSolution
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) {
            return false;
        }
        targetSum -= root->val;
        if (targetSum == 0 && !root->left && !root->right) {
            return true;
        }
        return hasPathSum(root->left, targetSum) || hasPathSum(root->right, targetSum);

    }
};
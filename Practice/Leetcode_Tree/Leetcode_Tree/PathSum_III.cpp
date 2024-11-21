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


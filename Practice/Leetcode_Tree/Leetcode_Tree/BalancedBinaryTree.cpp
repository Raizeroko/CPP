#include "Tree.h"

// MySolution
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }
        int left = maxDepth(root->left) + 1;
        int right = maxDepth(root->right) + 1;
        return left > right ? left : right;
    }

    bool isBalanced(TreeNode* root) {
        if (!root) {
            return true;
        }
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);
        int sub = abs(left - right);
        if (sub > 1)
            return false;
        return isBalanced(root->left) && isBalanced(root->right);
    }
};

// OptimSolution
class Solution {
private:
    bool ret = true;
public:
    int maxDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }
        int left = maxDepth(root->left) + 1;
        int right = maxDepth(root->right) + 1;
        if (abs(left - right) > 1) ret = false;
        return left > right ? left : right;
    }

    bool isBalanced(TreeNode* root) {
        maxDepth(root);
        return ret;
    }
};

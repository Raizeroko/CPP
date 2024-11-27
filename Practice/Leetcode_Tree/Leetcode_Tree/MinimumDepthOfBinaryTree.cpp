#include "Tree.h"

// MySolution
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }
        if (!root->left && !root->right) {
            return 1;
        }
        else if (!root->left) {
            return minDepth(root->right) + 1;
        }
        else if (!root->right) {
            return minDepth(root->left) + 1;
        }
        int left = minDepth(root->left) + 1;
        int right = minDepth(root->right) + 1;
        return left > right ? right : left;
    }
};


// OptimSolution
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }
        int left = minDepth(root->left);
        int right = minDepth(root->right);
        if (left == 0 || right == 0) {
            return left + right + 1;
        }
        return min(left, right) + 1;
    }
};

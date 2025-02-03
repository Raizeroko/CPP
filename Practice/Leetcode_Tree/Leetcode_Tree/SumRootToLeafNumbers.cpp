#include "Tree.h"

// MySolution
class Solution {
public:
    int _sumNumbers(TreeNode* root, int pathNum) {
        if (!root) {
            return 0;
        }
        pathNum = root->val + pathNum * 10;

        if (!root->left && !root->right) {
            return pathNum;
        }
        return _sumNumbers(root->left, pathNum) + _sumNumbers(root->right, pathNum);
    }

    int sumNumbers(TreeNode* root) {
        return _sumNumbers(root, 0);
    }
};
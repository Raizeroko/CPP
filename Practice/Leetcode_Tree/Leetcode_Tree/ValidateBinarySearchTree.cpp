#include "Tree.h"

// MySolution
class Solution {
public:
    bool _isValidBST(TreeNode* root, long left_min, long right_max) {
        if (!root) {
            return true;
        }
        if (root->val <= left_min || root->val >= right_max) {
            return false;
        }
        return _isValidBST(root->left, left_min, root->val) && _isValidBST(root->right, root->val, right_max);
    }

    bool isValidBST(TreeNode* root) {
        if (root == nullptr) return true;
        return _isValidBST(root, LONG_MIN, LONG_MAX);
    }
};


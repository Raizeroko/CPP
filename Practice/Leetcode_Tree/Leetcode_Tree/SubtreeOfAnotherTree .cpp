#include "Tree.h"

// MySolution
class Solution {
public:
    bool _isSubtree(TreeNode* root, TreeNode* subRoot) {
        if (!root && !subRoot) {
            return true;
        }
        else if (!root || !subRoot) {
            return false;
        }
        if (root->val != subRoot->val) {
            return false;
        }
        return _isSubtree(root->left, subRoot->left) && _isSubtree(root->right, subRoot->right);
    }

    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if (!root) {
            return false;
        }
        if (_isSubtree(root, subRoot)) {
            return true;
        }
        return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }
};
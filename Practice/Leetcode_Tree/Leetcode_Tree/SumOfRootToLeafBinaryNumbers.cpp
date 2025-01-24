#include "Tree.h"

// MySolution
class Solution {
public:
    int _sumRootToLeaf(TreeNode* root, int path) {
        if (!root) return 0;
        path *= 2;
        path += root->val;
        if (!root->left && !root->right) return path;
        return _sumRootToLeaf(root->left, path) + _sumRootToLeaf(root->right, path);

    }

    int sumRootToLeaf(TreeNode* root) {
        int path = 0;
        return _sumRootToLeaf(root, path);
    }
};
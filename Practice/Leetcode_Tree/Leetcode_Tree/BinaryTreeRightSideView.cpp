#include "Tree.h"

// MySolution
class Solution {
    vector<int> ret;
public:
    void _rightSideView(TreeNode* root, int level) {
        if (root == nullptr) return;
        if (level == ret.size()) ret.push_back(root->val);
        else ret[level] = root->val;
        _rightSideView(root->left, level + 1);
        _rightSideView(root->right, level + 1);
    }

    vector<int> rightSideView(TreeNode* root) {
        int level = 0;
        _rightSideView(root, level);
        return ret;
    }
};
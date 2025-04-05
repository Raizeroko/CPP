#include "Tree.h"

// MySolution
class Solution {
public:
    TreeNode* _flatten(TreeNode* root) {
        if (root == nullptr) return root;
        TreeNode* cur_l = root->left;
        TreeNode* cur_r = root->right;
        TreeNode* lowest = root;
        root->left = nullptr;
        if (cur_l) {
            root->right = cur_l;
            lowest = _flatten(cur_l);
        }
        if (cur_r) {
            lowest->right = cur_r;
            lowest = _flatten(cur_r);
        }
        return lowest;

    }

    void flatten(TreeNode* root) {
        _flatten(root);
    }
};
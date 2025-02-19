#include "Tree.h"

// MySolution
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) {
            return nullptr;
        }
        if (root == p) {
            return p;
        }
        if (root == q) {
            return q;
        }
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        if ((left == p && right == q) || (left == q && right == p)) {
            return root;
        }
        if (left) {
            return left;
        }
        if (right) {
            return right;
        }
        return left;
    }
};

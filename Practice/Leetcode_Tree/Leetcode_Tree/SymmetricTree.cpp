#include "Tree.h"

// MySolution
class Solution {
public:
    bool _isSymmetric(TreeNode* l, TreeNode* r) {
        if (!l && !r) {
            return true;
        }
        else if (!l || !r) {
            return false;
        }
        else if (l->val != r->val) {
            return false;
        }
        return _isSymmetric(l->left, r->right) && _isSymmetric(l->right, r->left);
    }

    bool isSymmetric(TreeNode* root) {
        if (!root)
            return true;
        return _isSymmetric(root->left, root->right);
    }
};


//
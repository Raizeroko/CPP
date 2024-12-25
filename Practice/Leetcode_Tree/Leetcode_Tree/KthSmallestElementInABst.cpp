#include "tree.h"

// MySolution
class Solution {
private:
    vector<int> v;
public:
    void _kthSmallest(TreeNode* root) {
        if (!root) {
            return;
        }
        v.push_back(root->val);
        _kthSmallest(root->left);
        _kthSmallest(root->right);
    }

    int kthSmallest(TreeNode* root, int k) {
        _kthSmallest(root);
        sort(v.begin(), v.end());
        return v[k - 1];
    }
};



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


// Review 2025/04/19
class Solution {
    int _k = 0;
    int _ret = 0;

    void _kthSmallest(TreeNode* root) {
        if (!root) return;
        if (_ret) return;
        _kthSmallest(root->left);
        _k--;
        if (_k == 0) {
            _ret = root->val;
        }
        _kthSmallest(root->right);
    }


public:
    int kthSmallest(TreeNode* root, int k) {
        _k = k;
        _kthSmallest(root);
        return _ret;
    }
};
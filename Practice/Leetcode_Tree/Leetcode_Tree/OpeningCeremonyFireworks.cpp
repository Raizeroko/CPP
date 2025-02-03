#include "Tree.h"

// MySolution
class Solution {
public:
    void _numColor(TreeNode* root, unordered_map <int, int>& harsh) {
        if (!root) {
            return;
        }
        harsh[root->val]++;
        _numColor(root->left, harsh);
        _numColor(root->right, harsh);
    }
    int numColor(TreeNode* root) {
        unordered_map <int, int> harsh;
        _numColor(root, harsh);
        return harsh.size();
    }
};
#include "Tree.h"

// MySolution
class Solution {
    int prek = 0;
public:
    TreeNode* _buildTree(vector<int>& preorder, vector<int>& inorder, TreeNode* cur, int left, int right) {
        if (prek == preorder.size()) return cur;
        if (left > right) return nullptr;
        int i = left;
        while (i <= right) {
            if (inorder[i] == preorder[prek]) break;
            i++;
        }
        cur = new TreeNode(preorder[prek]);
        prek++;
        cur->left = _buildTree(preorder, inorder, cur->left, left, i - 1);
        cur->right = _buildTree(preorder, inorder, cur->right, i + 1, right);
        return cur;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        TreeNode* cur;
        TreeNode* ret = _buildTree(preorder, inorder, cur, 0, inorder.size() - 1);
        return ret;
    }
};
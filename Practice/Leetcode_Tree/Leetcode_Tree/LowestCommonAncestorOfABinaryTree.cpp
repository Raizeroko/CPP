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

// Review 2025/04/09
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return nullptr;
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        // 当前节点是其中一个节点
        // 1.该节点第一个被找到，继续往上找，返回当前节点
        // 2.该节点是第二个被找到，当前节点就是结果，返回当前节点
        if (root == p || root == q) return root;
        // 左右分支各找到一个节点，那该节点就是公共祖先，返回该节点
        if (left && right) return root;
        // 左右分支有其中一个找到
        if (left) return left;
        if (right) return right;
        return nullptr;
    }
};

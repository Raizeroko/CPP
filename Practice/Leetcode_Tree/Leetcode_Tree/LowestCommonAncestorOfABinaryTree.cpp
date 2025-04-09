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
        // ��ǰ�ڵ�������һ���ڵ�
        // 1.�ýڵ��һ�����ҵ������������ң����ص�ǰ�ڵ�
        // 2.�ýڵ��ǵڶ������ҵ�����ǰ�ڵ���ǽ�������ص�ǰ�ڵ�
        if (root == p || root == q) return root;
        // ���ҷ�֧���ҵ�һ���ڵ㣬�Ǹýڵ���ǹ������ȣ����ظýڵ�
        if (left && right) return root;
        // ���ҷ�֧������һ���ҵ�
        if (left) return left;
        if (right) return right;
        return nullptr;
    }
};

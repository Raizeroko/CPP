#include "Tree.h"

// Nodecoder
// MySolution
class Solution {
public:
    bool isCompleteTree(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }

        queue<TreeNode*> tq;
        tq.push(root);
        bool flag = false; // 用来标记是否遇到过空节点

        while (!tq.empty()) {
            TreeNode* node = tq.front();
            tq.pop();

            // 如果之前遇到过空节点，现在遇到非空节点，说明不是完全二叉树
            if (node == nullptr) {
                flag = true;
            }
            else {
                // 如果之前遇到过空节点，现在遇到非空节点，则返回 false
                if (flag) {
                    return false;
                }

                // 将左右子节点加入队列，可能是空的
                tq.push(node->left);
                tq.push(node->right);
            }
        }

        return true;
    }
};
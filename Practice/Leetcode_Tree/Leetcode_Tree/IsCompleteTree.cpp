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
        bool flag = false; // ��������Ƿ��������սڵ�

        while (!tq.empty()) {
            TreeNode* node = tq.front();
            tq.pop();

            // ���֮ǰ�������սڵ㣬���������ǿսڵ㣬˵��������ȫ������
            if (node == nullptr) {
                flag = true;
            }
            else {
                // ���֮ǰ�������սڵ㣬���������ǿսڵ㣬�򷵻� false
                if (flag) {
                    return false;
                }

                // �������ӽڵ������У������ǿյ�
                tq.push(node->left);
                tq.push(node->right);
            }
        }

        return true;
    }
};
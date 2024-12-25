#include "Tree.h"

// MySolution
class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        queue<TreeNode*> q;
        int left = 0;
        if (!root) {
            return 0;
        }
        q.push(root);
        while (!q.empty()) {
            int n = q.size();
            left = q.front()->val;
            for (int i = n; i > 0; i--) {
                TreeNode* node = q.front();
                q.pop();
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
        }
        return left;
    }
};
#include "Tree.h"


// MySolution
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> q;
        vector<vector<int>> ret;
        if (root == nullptr) return vector<vector<int>>();
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            vector<int> level;
            while (size) {
                TreeNode* cur = q.front();
                q.pop();
                level.push_back(cur->val);
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
                size--;
            }
            ret.push_back(level);
            level.resize(0);
        }
        return ret;
    }
};
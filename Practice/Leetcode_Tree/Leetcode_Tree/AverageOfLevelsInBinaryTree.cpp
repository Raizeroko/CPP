#include "Tree.h"

// MySolution
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        queue<TreeNode*> s;
        vector<double> averages;
        if (!root) {
            return averages;
        }
        s.push(root);
        while (!s.empty()) {
            int n = s.size();
            double average = 0;
            for (int i = n; i > 0; i--) {
                TreeNode* node = s.front();
                s.pop();
                if (node->left) {
                    s.push(node->left);
                }
                if (node->right) {
                    s.push(node->right);
                }
                average += node->val;
            }
            average /= n;
            averages.push_back(average);
        }
        return averages;
    }
};
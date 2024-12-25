#include "Tree.h"

// MySolution
class Solution {
private:
    vector<int> v;
public:
    vector<int> preorderTraversal(TreeNode* root) {
        if (!root) {
            return vector<int>();
        }
        v.push_back(root->val);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
        return v;
    }
};

// Non-recursive
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*> s;
        vector<int> v;
        while (root || !s.empty()) {
            while (root) {
                v.push_back(root->val);
                s.push(root);
                root = root->left;
            }
            root = s.top();
            s.pop();
            root = root->right;
        }
        return v;
    }
};
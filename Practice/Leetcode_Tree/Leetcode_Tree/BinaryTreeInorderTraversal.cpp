#include "Tree.h"

// MySolution
class Solution {
private:
    vector<int> v;
public:
    vector<int> inorderTraversal(TreeNode* root) {
        if (!root) {
            return vector<int>();
        }
        inorderTraversal(root->left);
        v.push_back(root->val);
        inorderTraversal(root->right);
        return v;
    }
};


// Non-recursive
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> s;
        vector<int> v;
        while (root || !s.empty()) {
            // ����
            while (root) {
                s.push(root);
                root = root->left;
            }
            root = s.top();
            s.pop();
            v.push_back(root->val);
            root = root->right;
        }
        return v;
    }
};
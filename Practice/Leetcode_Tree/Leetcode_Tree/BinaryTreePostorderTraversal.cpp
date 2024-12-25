#include "Tree.h"

// MySolution
class Solution {
private:
    vector<int> v;

public:
    vector<int> postorderTraversal(TreeNode* root) {
        if (!root) {
            return vector<int>();
        }
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        v.push_back(root->val);
        return v;
    }
};


// Non-recursive
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode*> s;
        vector<int> v;
        TreeNode* prev = nullptr;
        while (root || !s.empty()) {
            while (root) {
                s.push(root);
                root = root->left;
            }
            root = s.top();
            s.pop();
            if (root->right && root->right != prev) {
                s.push(root);
                root = root->right;
            }
            else {
                v.push_back(root->val);
                prev = root;
                root = nullptr;
            }
        }
        return v;
    }
};
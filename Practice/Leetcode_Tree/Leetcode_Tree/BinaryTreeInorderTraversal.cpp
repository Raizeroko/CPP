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
            // ×î×ó
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


// Review 2025/04/19
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        TreeNode* cur = root;
        stack<TreeNode*> st;
        vector<int> ret;
        while (cur || !st.empty()) {
            while (cur) {
                st.push(cur);
                cur = cur->left;
            }
            ret.push_back(st.top()->val);
            cur = st.top()->right;
            st.pop();
        }

        return ret;
    }
};
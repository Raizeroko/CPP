#include "Tree.h"
#include <vector>
#include <queue>


// MySolution (29/71)
class Solution {
private:
    int ret = 0;
public:
    int _longestUnivaluePath(TreeNode* root, int fatherval) {
        if (!root) {
            return 0;
        }
        int left = _longestUnivaluePath(root->left, root->val);
        int right = _longestUnivaluePath(root->right, root->val);
        int tmp = left + right;
        if (root->val == fatherval) {
            tmp++;
            ret = max(ret, tmp);
        }
        return tmp;
    }


    int longestUnivaluePath(TreeNode* root) {
        if (!root) {
            return 0;
        }
        _longestUnivaluePath(root->left, root->val);
        _longestUnivaluePath(root->right, root->val);
        return ret;
    }
};

// MySolution 
class Solution {
private:
    int maxLength = 0;
public:
    pair<int, int> _longestUnivaluePath(TreeNode* root) {
        pair<int, int> ret(10000, 0);
        if (!root) {
            return ret;
        }
        pair<int, int> left = _longestUnivaluePath(root->left);
        pair<int, int> right = _longestUnivaluePath(root->right);
        if (root->val == left.first && root->val == right.first)
        {
            maxLength = max(maxLength, left.second + right.second + 1);
            ret.second = 1 + max(left.second, right.second);
            ret.first = root->val;
            return ret;
        }
        else if (root->val == left.first) {
            ret.second = 1 + left.second;
        }
        else if (root->val == right.first) {
            ret.second = 1 + right.second;
        }
        else
        {
            ret.second = 1;
        }
        ret.first = root->val;
        maxLength = max(maxLength, ret.second);
        return ret;

    }
    int longestUnivaluePath(TreeNode* root) {
        if (!root) {
            return 0;
        }
        _longestUnivaluePath(root);
        if (maxLength != 0) {
            maxLength--;
        }
        return maxLength;
    }
};


// OptimSolution
class Solution {
private:
    int maxLength = 0;
public:
    pair<int, int> _longestUnivaluePath(TreeNode* root) {
        pair<int, int> ret(100000, 0);
        if (!root) {
            return ret;
        }
        pair<int, int> left = _longestUnivaluePath(root->left);
        pair<int, int> right = _longestUnivaluePath(root->right);
        int leftMax = 0;
        int rightMax = 0;
        if (root->val == left.first) {
            leftMax = left.second + 1;
        }
        if (root->val == right.first) {
            rightMax = right.second + 1;
        }
        maxLength = max(maxLength, leftMax + rightMax);
        ret.first = root->val;
        ret.second = max(leftMax, rightMax);
        return ret;

    }
    int longestUnivaluePath(TreeNode* root) {
        if (!root) {
            return 0;
        }
        _longestUnivaluePath(root);

        return maxLength;
    }
};


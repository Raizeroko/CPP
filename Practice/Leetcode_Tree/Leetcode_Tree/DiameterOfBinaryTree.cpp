#include "Tree.h"


// MySolution
class Solution {
public:
    int depth(TreeNode* root) {
        if (!root) {
            return 0;
        }
        int left = depth(root->left) + 1;
        int right = depth(root->right) + 1;
        return left > right ? left : right;
    }
    int diameterOfBinaryTree(TreeNode* root) {
        if (!root) {
            return 0;
        }
        int leftd = depth(root->left);
        int rightd = depth(root->right);
        int left = diameterOfBinaryTree(root->left);
        int right = diameterOfBinaryTree(root->right);
        if (leftd + rightd < left)
        {
            return left;
        }
        else if (leftd + rightd < right)
        {
            return right;
        }
        else
        {
            return leftd + rightd;
        }
    }
};

//OptimSolution
class Solution {
    
private: 
    int ret=0;

public:
    int depth(TreeNode* root){
        if(!root){
            return 0;
        }
        int left = depth(root->left);
        int right = depth(root->right);
        ret = left+right>ret ? left+right : ret;
        return std::max(left, right)+1;
    }

    int diameterOfBinaryTree(TreeNode* root) {
        depth(root);
        return ret;
    }
};
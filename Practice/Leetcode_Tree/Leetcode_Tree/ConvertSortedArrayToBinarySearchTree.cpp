#include "Tree.h"

// MySolution
class Solution {
public:

    TreeNode* ToBST(const vector<int>& nums, int left, int right) {
        if (left > right) {
            return nullptr;
        }
        int mid = left + (right - left) / 2;
        TreeNode* midNode = new TreeNode(nums[mid]);
        midNode->left = ToBST(nums, left, mid - 1);
        midNode->right = ToBST(nums, mid + 1, right);
        return midNode;
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
        TreeNode* ret = ToBST(nums, 0, nums.size() - 1);
        return ret;
    }
};


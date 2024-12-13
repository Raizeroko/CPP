#include "Tree.h"

// MySolution(75/124)
class Solution {
public:
    Solution()
        :withRoot(0)
        , withoutRoot(0)
    {
    }
    void _rob(TreeNode* root, bool flag) {
        if (!root) {
            return;
        }
        int isNeighbor = 0;
        int notNeighbor = 0;
        _rob(root->left, !flag);
        _rob(root->right, !flag);
        if (flag == 0) {
            isNeighbor = withRoot;
            notNeighbor = withoutRoot;
            notNeighbor += root->val;
            withoutRoot = isNeighbor > notNeighbor ? isNeighbor : notNeighbor;

        }
        else {
            // flag==1
            isNeighbor = withoutRoot;
            notNeighbor = withRoot;
            notNeighbor += root->val;
            withRoot = isNeighbor > notNeighbor ? isNeighbor : notNeighbor;
        }

        return;
    }

    int rob(TreeNode* root) {
        _rob(root, true);
        return withRoot > withoutRoot ? withRoot : withoutRoot;
    }

private:
    int withRoot;
    int withoutRoot;
};

// OptimSolution
class Solution {
public:
    // ret[0]: 不抢劫该位置， ret[1]: 抢劫该位置
    vector<int> _rob(TreeNode* root) {
        vector<int> ret(2, 0);
        if (!root) {
            return ret;
        }
        vector<int> left = _rob(root->left);
        vector<int> right = _rob(root->right);
        ret[0] = max(left[0], left[1]) + max(right[0], right[1]);
        ret[1] = left[0] + right[0] + root->val;
        return ret;
    }

    int rob(TreeNode* root) {
        vector<int> ret(2);
        ret = _rob(root);
        return max(ret[0], ret[1]);
    }
};
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

// 
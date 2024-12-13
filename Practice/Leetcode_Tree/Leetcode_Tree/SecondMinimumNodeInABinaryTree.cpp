#include "Tree.h"
#include <vector>

using namespace std;

// MySolution
class Solution {
private:
    vector<int> ret = { -1, -1 };
public:
    void _findSecondMinimumValue(TreeNode* root) {
        if (!root) {
            return;
        }
        _findSecondMinimumValue(root->left);
        _findSecondMinimumValue(root->right);
        if (ret[0] == -1 || root->val < ret[0]) {
            if (ret[1] == -1 || ret[0] < ret[1]) {
                ret[1] = ret[0];
            }
            ret[0] = root->val;
        }
        else if (root->val > ret[0]) {
            if (ret[1] == -1 || root->val < ret[1]) {
                ret[1] = root->val;
            }
        }
    }

    int findSecondMinimumValue(TreeNode* root) {
        _findSecondMinimumValue(root);
        return ret[1];
    }
};
#include "Vector.h"

// MySolution
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int left = 0, right = matrix[0].size() - 1;
        int up = 0, down = matrix.size() - 1;
        vector<int> ret;
        while (true) {
            for (int i = left; i <= right; i++) {
                ret.push_back(matrix[up][i]);
            }
            up++;
            if (up > down) break;
            for (int i = up; i <= down; i++) {
                ret.push_back(matrix[i][right]);
            }
            right--;
            if (left > right) break;
            for (int i = right; i >= left; i--) {
                ret.push_back(matrix[down][i]);
            }
            down--;
            if (up > down) break;
            for (int i = down; i >= up; i--) {
                ret.push_back(matrix[i][left]);
            }
            left++;
            if (left > right) break;
        }
        return ret;
    }
};
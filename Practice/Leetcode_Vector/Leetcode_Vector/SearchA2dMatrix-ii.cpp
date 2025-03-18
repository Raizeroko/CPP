#include "Vector.h"

// MySolution
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int i = matrix.size() - 1;
        int j = 0;
        while (i >= 0 && j < matrix[0].size()) {
            if (matrix[i][j] == target) {
                return true;
            }
            // 当前j列必然所有数都比target小
            if (matrix[i][j] < target) {
                j++;
            }
            else {
                i--;
            }
        }
        return false;
    }
};


// Review 2025/03/18
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int i = matrix.size() - 1;
        int j = 0;
        while (i >= 0 && j <= matrix[0].size() - 1) {
            if (matrix[i][j] == target) {
                return true;
            }
            else if (matrix[i][j] > target) {
                i--;
            }
            else {
                j++;
            }
        }
        return false;
    }
};s
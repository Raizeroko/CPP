#include "DP.h"

// MySolution
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> path(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) path[i][j] = grid[i][j];
                else if (i == 0) path[i][j] = path[i][j - 1] + grid[i][j];
                else if (j == 0) path[i][j] = path[i - 1][j] + grid[i][j];
                else path[i][j] = min(path[i][j - 1], path[i - 1][j]) + grid[i][j];
            }
        }
        return path[m - 1][n - 1];
    }
};
#include "Puzzle.h"

// MySolution
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        vector<vector<int>> dp(obstacleGrid.size(), vector<int>(obstacleGrid[0].size(), 0));
        for (int i = 0; i < obstacleGrid.size(); i++) {
            for (int j = 0; j < obstacleGrid[0].size(); j++) {
                int left;
                int up;
                if (obstacleGrid[i][j] == 1) {
                    left = 0;
                    up = 0;
                }
                else if (i == 0 && j == 0) {
                    left = 0;
                    up = 1;
                }
                else if (i == 0) {
                    left = dp[i][j - 1];
                    up = 0;
                }
                else if (j == 0) {
                    up = dp[i - 1][j];
                    left = 0;
                }
                else {
                    left = dp[i][j - 1];
                    up = dp[i - 1][j];
                }
                dp[i][j] = left + up;
            }
        }
        return dp.back().back();
    }
};
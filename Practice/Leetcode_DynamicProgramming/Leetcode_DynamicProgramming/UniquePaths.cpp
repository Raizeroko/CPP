#include "DP.h"

// MySolution
class Solution {
public:
    int uniquePaths(int m, int n) {
        // C(m+n-2, m-1)
        long long result = 1;
        int smaller = min(m - 1, n - 1);
        for (int i = 1; i <= smaller; i++) {
            result *= (m + n - 1 - i);
            result /= i;
        }
        return result;
    }
};

// OptimSolution
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> path(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            path[i][0] = 1;
        }
        for (int j = 0; j < n; j++) {
            path[0][j] = 1;
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                path[i][j] = path[i][j - 1] + path[i - 1][j];
            }
        }
        return path[m - 1][n - 1];
    }
};
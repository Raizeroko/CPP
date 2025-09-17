#include "Puzzle.h"

// MySolution
class Solution {
public:

    vector<vector<int>> path;
    vector<vector<bool>> memo;

    const int dirs[4][2] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };


    bool isValid(int i, int j) {
        if (i < 0 || j < 0 || i >= path.size() || j >= path[0].size()) return false;
        return true;
    }

    int dfs(int i, int j, vector<vector<int>>& matrix) {
        if (memo[i][j] == true) {
            return path[i][j];
        }
        int flag = 0;
        for (auto dir : dirs) {
            int nexti = i + dir[0];
            int nextj = j + dir[1];
            if (isValid(nexti, nextj) && matrix[i][j] < matrix[nexti][nextj]) {
                path[i][j] = max(path[i][j], dfs(nexti, nextj, matrix) + 1);
                memo[i][j] = true;
                flag = 1;
            }
        }
        if (flag == 0) {
            path[i][j] = 1;
            memo[i][j] = true;
            return 1;
        }
        return path[i][j];
    }

    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        path.assign(m, vector<int>(n, 0));
        memo.assign(m, vector<bool>(n, false));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                dfs(i, j, matrix);
            }
        }
        int max = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (path[i][j] > max) max = path[i][j];
            }
        }
        return max;
    }
};
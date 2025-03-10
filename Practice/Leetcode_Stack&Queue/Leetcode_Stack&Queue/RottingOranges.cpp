#include "Stack&Queue.h"

// MySolution
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        queue<pair<int, int>> q;
        int dirs[4][2] = { {0, 1},{0, -1},{1, 0},{-1, 0} };
        int m = grid.size();
        int n = grid[0].size();
        // ³õÊ¼éÙ×Ó
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 2) {
                    q.push(make_pair(i, j));
                }
            }
        }
        int ret = 0;
        int k = q.size();
        while (!q.empty()) {
            if (k == 0) {
                ret++;
                k = q.size();
            }
            pair<int, int> p = q.front();
            q.pop();
            for (auto dir : dirs) {
                int i = p.first + dir[0];
                int j = p.second + dir[1];
                if (i >= 0 && i < m && j >= 0 && j < n && grid[i][j] == 1) {
                    grid[i][j] = 2;
                    q.push(make_pair(i, j));
                }
            }
            k--;
        }
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == 1)
                    return -1;
        return ret;
    }
};

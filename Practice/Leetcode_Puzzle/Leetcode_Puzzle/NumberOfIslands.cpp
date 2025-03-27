#include "Puzzle.h"

// MySolution
class Solution {
    bool truePos(vector<vector<char>>& grid, int i, int j) {
        if (i < 0 || i >= grid.size()) {
            return false;
        }
        if (j < 0 || j >= grid[i].size()) {
            return false;
        }
        if (grid[i][j] == '0') {
            return false;
        }
        return true;
    }
    bool _numIslands(vector<vector<char>>& grid, int i, int j) {
        if (grid[i][j] == '0') {
            return false;
        }
        else {
            grid[i][j] = '0';
            if (truePos(grid, i - 1, j))
                _numIslands(grid, i - 1, j);
            if (truePos(grid, i, j - 1))
                _numIslands(grid, i, j - 1);
            if (truePos(grid, i, j + 1))
                _numIslands(grid, i, j + 1);
            if (truePos(grid, i + 1, j))
                _numIslands(grid, i + 1, j);
        }
        return true;
    }

public:
    int numIslands(vector<vector<char>>& grid) {
        int ret = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (truePos(grid, i, j) && _numIslands(grid, i, j)) {
                    ret++;
                }
            }
        }
        return ret;
    }
};


// Review 2025/03/27
class Solution {
private:
    int m;
    int n;
    vector<vector<bool>> arrived;
public:
    vector<pair<int, int>> truePos(const vector<vector<char>> grid, int i, int j) {
        vector<pair<int, int>> true_pos;
        if (i - 1 >= 0 && !arrived[i - 1][j] && grid[i - 1][j] == '1')   true_pos.push_back(make_pair(i - 1, j));
        if (i + 1 < m && !arrived[i + 1][j] && grid[i + 1][j] == '1')   true_pos.push_back(make_pair(i + 1, j));
        if (j - 1 >= 0 && !arrived[i][j - 1] && grid[i][j - 1] == '1')   true_pos.push_back(make_pair(i, j - 1));
        if (j + 1 < n && !arrived[i][j + 1] && grid[i][j + 1] == '1')   true_pos.push_back(make_pair(i, j + 1));
        return true_pos;
    }

    void aroundLand(const vector<vector<char>> grid, int i, int j) {
        vector<pair<int, int>> true_pos = truePos(grid, i, j);
        arrived[i][j] = true;
        for (auto cur : true_pos) {
            aroundLand(grid, cur.first, cur.second);
        }
        return;
    }

    int numIslands(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();
        arrived = vector<vector<bool>>(m, vector<bool>(n, false));
        int ret = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!arrived[i][j] && grid[i][j] == '1') {
                    // 没来过的陆地
                    aroundLand(grid, i, j);
                    ret++;
                }
            }
        }
        return ret;
    }

};

// OptimSolution
class Solution {
private:
    int m;
    int n;
    vector<vector<bool>> arrived;

public:
    void dfs(vector<vector<char>>& grid, int i, int j) {
        // 显式栈替代递归
        stack<pair<int, int>> stk;
        stk.push({ i, j });
        arrived[i][j] = true;

        while (!stk.empty()) {
            // C++17: 结构化绑定
            auto [x, y] = stk.top();
            stk.pop();

            // 遍历四个方向
            for (auto [dx, dy] : vector<pair<int, int>>{ {-1, 0}, {1, 0}, {0, -1}, {0, 1} }) {
                int nx = x + dx, ny = y + dy;

                // 判断是否是有效的陆地
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && !arrived[nx][ny] && grid[nx][ny] == '1') {
                    arrived[nx][ny] = true;
                    stk.push({ nx, ny });
                }
            }
        }
    }

    int numIslands(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();
        arrived = vector<vector<bool>>(m, vector<bool>(n, false));
        int ret = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!arrived[i][j] && grid[i][j] == '1') {
                    // 没来过的陆地，启动搜索
                    dfs(grid, i, j);
                    ret++;
                }
            }
        }
        return ret;
    }
};
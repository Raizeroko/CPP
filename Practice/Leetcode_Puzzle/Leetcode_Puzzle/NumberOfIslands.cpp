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
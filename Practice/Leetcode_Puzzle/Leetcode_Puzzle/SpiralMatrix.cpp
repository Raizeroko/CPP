#include "Puzzle.h"

// MySolution
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ret;
        int up = 0;
        int right = matrix[0].size() - 1;
        int down = matrix.size() - 1;
        int left = 0;
        while (left <= right && up <= down) {
            // up
            int i = up, j = left;
            while (i == up && j < right)
            {
                ret.push_back(matrix[up][j]);
                j++;
            }

            // right
            while (j == right && i < down)
            {
                ret.push_back(matrix[i][right]);
                i++;
            }
            // down    
            while (i == down && j > left)
            {
                ret.push_back(matrix[down][j]);
                j--;
            }
            // left
            while (j == left && i > up)
            {
                ret.push_back(matrix[i][left]);
                i--;
            }
            up++;
            right--;
            down--;
            left++;
            cout << "up: " << up << endl;
            cout << "right: " << right << endl;
            cout << "down: " << down << endl;
            cout << "left: " << left << endl;
        }
        return ret;
    }
};


// OptimSolution
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ret;
        int up = 0;
        int right = matrix[0].size() - 1;
        int down = matrix.size() - 1;
        int left = 0;
        while (left <= right && up <= down) {
            // up
            for (int i = left; i <= right; i++) {
                ret.push_back(matrix[up][i]);
            }
            for (int j = up + 1; j <= down; j++) {
                ret.push_back(matrix[j][right]);
            }
            if (left < right&& up < down) {
                for (int i = right - 1; i > left; i--) {
                    ret.push_back(matrix[down][i]);
                }
                for (int j = down; j > up; j--) {
                    ret.push_back(matrix[j][left]);
                }
            }
            up++;
            right--;
            down--;
            left++;
        }

        return ret;
    }
};

// UpdateMySolution
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ret;
        int up = 0;
        int right = matrix[0].size() - 1;
        int down = matrix.size() - 1;
        int left = 0;
        while (true) {
            // up:left->right
            if (up > down) break;
            for (int i = left; i <= right; i++) {
                ret.push_back(matrix[up][i]);
            }
            up++;
            // right:up->down
            if (left > right) break;
            for (int i = up; i <= down; i++) {
                ret.push_back(matrix[i][right]);
            }
            right--;
            // down:right->left
            if (up > down) break;
            for (int i = right; i >= left; i--) {
                ret.push_back(matrix[down][i]);
            }
            down--;
            // left:down->up
            if (left > right)   break;
            for (int i = down; i >= up; i--) {
                ret.push_back(matrix[i][left]);
            }
            left++;
        }
        return ret;
    }
};
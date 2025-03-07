#include "Vector.h"

// MySolution
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        unordered_set<int> harshi;
        unordered_set<int> harshj;
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                if (matrix[i][j] == 0) {
                    harshi.insert(i);
                    harshj.insert(j);
                }
            }
        }
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                if (harshi.count(i) || harshj.count(j)) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};

// OptimSolution
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        // 是否第0行，第0列本来就有0
        int flagi = 0;
        int flagj = 0;
        for (int i = 0; i < matrix.size(); i++) {
            if (matrix[i][0] == 0) {
                flagi = 1;
            }
        }
        for (int j = 0; j < matrix[0].size(); j++) {
            if (matrix[0][j] == 0) {
                flagj = 1;
            }
        }
        for (int i = 1; i < matrix.size(); i++) {
            for (int j = 1; j < matrix[i].size(); j++) {
                if (matrix[i][j] == 0) {
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }
        for (int i = 1; i < matrix.size(); i++) {
            for (int j = 1; j < matrix[i].size(); j++) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }
        if (flagi) {
            for (int i = 0; i < matrix.size(); i++) {
                matrix[i][0] = 0;
            }
        }
        if (flagj) {
            for (int j = 0; j < matrix[0].size(); j++) {
                matrix[0][j] = 0;
            }
        }

    }
};
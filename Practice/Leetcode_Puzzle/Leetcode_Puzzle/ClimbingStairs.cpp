#include "Puzzle.h"

// MySolution
class Solution {
public:
    int climbStairs(int n) {
        int step[2] = { 1, 2 };
        if (n <= 2) {
            return step[n - 1];
        }
        else {
            while (n-- > 2) {
                int tmp = step[0] + step[1];
                step[0] = step[1];
                step[1] = tmp;
            }
        }
        return step[1];
    }
};


// Review(2025_01_10)
class Solution {
public:
    int climbStairs(int n) {
        pair<int, int> climbSteps(1, 1);
        while (n-- > 1) {
            pair<int, int> tmp(climbSteps.second, climbSteps.first + climbSteps.second);
            climbSteps = tmp;
        }
        return climbSteps.second;
    }
};

#include "Puzzle.h"


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



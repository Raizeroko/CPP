#include "DP.h"

// MySolution
class Solution {
public:
    int numSquares(int n) {
        vector<int> v(n + 1, n);
        v[0] = 0;
        v[1] = 1;
        for (int i = 2; i < n + 1; i++) {
            for (int j = 1; j * j <= i; j++) {
                v[i] = min(v[i], v[i - j * j]);
            }
            v[i] += 1;
        }
        return v[n];
    }
};
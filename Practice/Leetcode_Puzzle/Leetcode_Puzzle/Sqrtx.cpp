#include "Puzzle.h"

// MySolution
class Solution {
public:
    int mySqrt(int x) {
        if (x == 0) {
            return 0;
        }
        double x0 = x;
        while (true) {
            double x1 = (x0 + (double)x / x0) * 0.5;
            if (fabs(x0 - x1) < 1e-7) break;
            x0 = x1;
        }
        return (int)x0;
    }
};
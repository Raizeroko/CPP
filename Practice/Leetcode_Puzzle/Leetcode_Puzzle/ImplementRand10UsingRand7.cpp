#include "Puzzle.h"

int rand7() {};

// MySolution
class Solution {
public:
    int rand10() {
        int x;
        do {
            // 等概率生成[1,49]
            x = 7 * (rand7() - 1) + rand7();
        } while (x > 40);
        x = x % 10 + 1;
        return x;
    }
};
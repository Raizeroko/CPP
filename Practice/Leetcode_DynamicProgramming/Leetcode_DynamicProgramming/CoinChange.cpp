#include "DP.h"

// MySolution
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> step(amount + 1, amount + 1);
        step[0] = 0;
        for (int i = 1; i < step.size(); i++) {
            for (auto coin : coins) {
                if (i - coin >= 0) {
                    step[i] = min(step[i], step[i - coin] + 1);
                }
            }
        }
        if (step.back() > amount) return -1;
        return step.back();
    }
};
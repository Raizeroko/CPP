#include "DP.h"

// MySolution
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minPrc = prices[0];
        int maxPrft = 0;
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] < minPrc) {
                minPrc = prices[i];
            }
            if (prices[i] - minPrc > maxPrft) {
                maxPrft = prices[i] - minPrc;
            }
        }
        return maxPrft;
    }
};
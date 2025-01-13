#include "DP.h"

// MySolution
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // hold:vecotr[i].first;
        // unhold:vector[i].second
        vector<pair<int, int>> dp(prices.size(), make_pair(1, 1));
        dp[0].first = 0 - prices[0];
        dp[0].second = 0;
        for (int i = 1; i < prices.size(); i++) {
            dp[i].first = max(dp[i - 1].first, dp[i - 1].second - prices[i]);
            dp[i].second = max(dp[i - 1].first + prices[i], dp[i - 1].second);
        }
        return max(dp.back().first, dp.back().second);
    }
};


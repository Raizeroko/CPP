#include <vector>

using namespace std;

// MySolution
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        vector<vector<int>> profit(n, vector<int>(2));
        profit[0][0] = 0;
        profit[0][1] = -prices[0];
        for (int i = 1; i < n; i++) {
            profit[i][0] = max(profit[i - 1][0], profit[i - 1][1] + prices[i] - fee);
            profit[i][1] = max(profit[i - 1][1], profit[i - 1][0] - prices[i]);
        }
        return profit[n - 1][0];

    }
};
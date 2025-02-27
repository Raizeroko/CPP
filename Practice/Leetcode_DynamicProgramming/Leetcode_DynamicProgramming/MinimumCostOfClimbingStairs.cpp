#include "DP.h"

// Nowcoder
// MySolution
int main() {
    vector<int> cost;
    int c;
    while (scanf("%d,", &c) > 0) { // 注意 while 处理多个 case
        cost.push_back(c);
    }
    vector<vector<int>> dp(cost.size() + 1, vector<int>(2, 0));
    for (int i = 2; i < cost.size() + 1; i++) {
        dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]) + cost[i - 1];
        dp[i][1] = min(dp[i - 2][0], dp[i - 2][1]) + cost[i - 2];
    }
    cout << min(dp.back()[0], dp.back()[1]);
}
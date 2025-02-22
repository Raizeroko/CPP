#include "DP.h"

// Nowcoder
// MySolution
int main() {
    int n;
    vector<int> v;
    cin >> n;
    int tmp;
    while (cin >> tmp) {
        v.push_back(tmp);
    }
    vector<int> dp(v.size());
    dp[0] = v[0];
    int max = dp[0];
    for (int i = 1; i < v.size(); i++) {
        dp[i] = std::max(v[i], dp[i - 1] + v[i]);
        if (dp[i] > max) {
            max = dp[i];
        }
    }
    cout << max;
}
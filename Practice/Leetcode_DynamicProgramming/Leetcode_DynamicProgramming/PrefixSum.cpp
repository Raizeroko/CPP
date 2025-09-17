#include "DP.h"
using namespace std;
using ll = long long;
int main() {
    ll n, m;
    cin >> n >> m;
    vector<ll> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    vector<vector<ll>> query(m, vector<ll>(2));
    for (int i = 0; i < m; i++) {
        cin >> query[i][0] >> query[i][1];
    }
    vector<ll> dp(n + 1, 0);
    for (int i = 0; i < n; i++) {
        dp[i + 1] = dp[i] + arr[i];
    }

    for (int i = 0; i < m; i++) {
        cout << dp[query[i][1]] - dp[query[i][0] - 1] << endl;
    }
}
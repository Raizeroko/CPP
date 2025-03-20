#include <iostream>
using namespace std;

// MySolution
int main() {
    int n; 
    cin >>n;
    int cur = abs(n);
    int step = 0;
    while(cur){
        if(cur%2 == 0) cur/=2;
        else cur += ((cur+1)/2%2==0 && cur > 3) ? 1 : -1;
        step++;
    }
    cout << step;
}


// OptimSolution
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n; 
    cin >> n;
    n = abs(n);
    int cur = 0;
    int step = 0;
    vector<int> dp(n+1);
    dp[0] = 0;
    for(int i = 1; i <= n; i++)
    {
        if(i%2 == 0){
            dp[i] = dp[i/2]+1;
        }
        else{
            dp[i] = min(dp[i-1], dp[(i+1)/2]+1)+1;
        }
    }
    cout << dp[n];
}

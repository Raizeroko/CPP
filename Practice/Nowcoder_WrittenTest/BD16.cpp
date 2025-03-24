#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, x1, y1, x2, y2;
    cin >> n >> x1 >> y1 >> x2 >> y2;
    
    // 存储每朵花到两个喷泉的距离平方
    vector<pair<long, long>> v;
    for(long i = 0; i < n; i++) {
        int xf, yf;
        cin >> xf >> yf;
        v.push_back({
            pow(xf - x1, 2) + pow(yf - y1, 2),  // 到第一个喷泉的距离平方
            pow(xf - x2, 2) + pow(yf - y2, 2)   // 到第二个喷泉的距离平方
        });
    }
    
    // 按到第一个喷泉的距离排序
    sort(v.begin(), v.end());
    
    // 初始化答案和第二个喷泉的最大覆盖半径
    long ans = v[n-1].first;
    long jMax = v[n-1].second;
    
    // 从后向前遍历
    for(int i = n-2; i >= 0; i--) {
        ans = min(ans, v[i].first + jMax);  // 更新最优解
        jMax = max(jMax, v[i].second);      // 更新第二个喷泉的最大覆盖半径
    }
    
    cout << min(ans, jMax) << endl;
    return 0;
}

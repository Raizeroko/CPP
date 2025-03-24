// MySolution (Can't pass)
#include <functional>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

long long fn(const vector<int>& a, int n) {
    long long ret = 0;
    long long power = 1; // 预计算 n^i
    for (int i = 0; i < a.size(); i++) {
        ret += a[i] * power;
        power *= n;
        if (ret < 0) break; // 防止溢出，提前退出
    }
    return ret;
}

int main() {
    int k;
    cin >> k;
    vector<vector<int>> A(k, vector<int>(8, 0));
    for (int i = 0; i < k; i++) {
        cin >> A[i][7] >> A[i][6] >> A[i][5] >> A[i][4] >> A[i][3] >> A[i][2] >> A[i][1]
            >> A[i][0];
    }
    int n;
    cin >> n;
    priority_queue<long long> pq;
    for (int i = 1; i <= n / k + 1; i++) {
        for (int j = 0; j < k; j++) {
            int tmp = fn(A[j], i);
            if (pq.empty() || pq.size() < n || tmp < pq.top()) {
                if (pq.size() == n)  pq.pop();
                pq.push(tmp);

            }

        }
    }

    cout << pq.top();
}



// OptimSolution
#include <bits/stdc++.h>
using namespace std;
const int N = 8;
 
struct Node {
    long value;
    int id;
};
 
struct cmp {
    bool operator()(const Node &a, const Node &b) {
        return a.value > b.value;
    }
};
 
// 使用霍纳法则计算多项式值
int compute(vector<int> &seq, int n) {
    long ret = seq[0];
    for(int i = 1; i < N; i++) {
        ret = ret * n + seq[i];
    }
    return ret;
}
 
int main() {
    int k = 0, n = 0;
    scanf("%d", &k);
    vector<vector<int>> seq(k, vector<int>(N, 0));
     
    // 读入k个多项式的系数
    for(int i = 0; i < k; i++) {
        for(int j = 0; j < N; j++) {
            scanf("%d", &seq[i][j]);
        }
    }
    scanf("%d", &n);
     
    // 初始化优先队列和每个序列的下一个位置
    priority_queue<Node, vector<Node>, cmp> q;
    vector<int> next(k, 1);
    long val = 0;
     
    // 将每个序列的第一个值加入队列
    for(int i = 0; i < k; i++) {
        val = compute(seq[i], next[i]);
        q.push({val, i});
        ++next[i];
    }
     
    // 找第n小的数
    while(--n) {
        Node cur = q.top(); q.pop();
        val = compute(seq[cur.id], next[cur.id]);
        q.push({val, cur.id});
        ++next[cur.id];
    }
     
    cout << q.top().value << endl;
    return 0;
}
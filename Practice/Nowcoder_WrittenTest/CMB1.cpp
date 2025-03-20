#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    string input;
    getline(cin ,input);
    stringstream ss;
    ss.str(input);
    vector<int> v;
    int n = 0;
    while (ss >> n) {  // 检查读取是否成功
        v.push_back(n);
    }
    sort(v.begin(), v.end());
    for(int i = 0; i < v.size(); i++){
        if(v[i] != i){
            cout << i;
            break;
        }
    }
}
// 64 位输出请用 printf("%lld")
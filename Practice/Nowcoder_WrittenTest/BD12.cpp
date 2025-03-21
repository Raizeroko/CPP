#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    string input;
    cin >> input;
    string ret;
    char max = 'a' - 1;
    for(int i = input.size() - 1; i >=0; i--){
        if(input[i] >= max){
            ret += input[i];
            max = input[i];
        }
    }
    reverse(ret.begin(), ret.end());
    cout << ret;
}
// 64 位输出请用 printf("%lld")
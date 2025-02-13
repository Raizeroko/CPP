#include "Puzzle.h"

// Nowcoder
// MySolution
long long int GetDivisor(long long int num) {
    long long int ret = 0;
    for (int i = 1; i <= num; i += 2) {
        ret += i;
    }
    return ret;
}

int main() {
    int a, b;
    while (cin >> a) { // 注意 while 处理多个 case
        long long int ret = 0;
        while (a) {
            // cout << GetDivisor(i) << endl;
            ret += GetDivisor(a);
            a /= 2;
        }
        cout << ret << endl;

    }
}
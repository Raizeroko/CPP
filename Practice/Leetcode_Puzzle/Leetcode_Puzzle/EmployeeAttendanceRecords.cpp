#include "Puzzle.h"

// Nowcoder
// MySolution
int main() {
    int n;
    while (cin >> n) { // 注意 while 处理多个 case
        // Cn^0 = 1
        // Cn^1 = n
        // Cn^2 = n!/(2!*(n-2)!) = n*(n-1)/2
        int ret = n * (n - 1) / 2;
        ret += 1;
        ret += n;
        cout << ret;
    }
}
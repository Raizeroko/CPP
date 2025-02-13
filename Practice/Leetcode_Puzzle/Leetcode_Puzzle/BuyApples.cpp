#include "Puzzle.h"

// Nowcoder
// MySolution
int main() {
    int a;
    int ret = -1;
    while (cin >> a) { // 注意 while 处理多个 case
        for (int smallBag = 0; smallBag * 6 <= a; smallBag++) {
            int bigBagApples = a - smallBag * 6;
            if (bigBagApples % 8 == 0) {
                int bigBag = bigBagApples / 8;
                ret = smallBag + bigBag;
                break;
            }
        }
        cout << ret;
    }
}
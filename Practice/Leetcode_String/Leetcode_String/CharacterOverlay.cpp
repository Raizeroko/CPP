#include "String.h"

// nowcoder
// MySolution
int main() {
    string s, t;
    while (cin >> s >> t) { // 注意 while 处理多个 case
        sort(t.begin(), t.end());
        for (char& c : s) {
            char tmp = t.back();
            if (c < tmp) {
                c = tmp;
                t.pop_back();
            }

        }
        cout << s;
    }
}
#include "harsh.h"

// Nowcoder
// MySolution
int main() {
    string input;
    unordered_set<char> harsh;
    while (cin >> input) { // 注意 while 处理多个 case
        for (auto e : input) {
            harsh.insert(e);
        }
        if (harsh.size() > 2) {
            cout << 0;
        }
        else if (harsh.size() == 2) {
            cout << 2;
        }
        else if (harsh.size() == 1) {
            cout << 1;
        }
    }
}
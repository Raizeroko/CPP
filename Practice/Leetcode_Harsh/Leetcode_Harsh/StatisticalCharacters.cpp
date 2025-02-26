#include "harsh.h"

// Nowcoder
// MySolution
int main() {
    string s;
    unordered_map<char, int> harsh;
    getline(cin, s);
    for (auto c : s) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            int& cur = harsh[c];
            if (cur == 2) {
                cout << c;
                break;
            }
            cur++;
        }

    }
}
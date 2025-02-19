#include "Harsh.h"

// Nowcoder
// MySolution
int main() {
    string inputString, removeLetters;
    while (getline(cin, inputString)) { // ע�� while ������ case
        cin >> removeLetters;
        unordered_set<char> harsh;
        for (auto c : removeLetters) {
            harsh.insert(c);
        }
        for (auto cur = inputString.begin(); cur != inputString.end();) {
            if (harsh.count(*cur)) {
                cur = inputString.erase(cur);
                continue;
            }
            cur++;
        }
        cout << inputString;
    }
}
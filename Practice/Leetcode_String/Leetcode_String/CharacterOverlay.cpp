#include "String.h"

// nowcoder
// MySolution
int main() {
    string s, t;
    while (cin >> s >> t) { // ע�� while ������ case
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
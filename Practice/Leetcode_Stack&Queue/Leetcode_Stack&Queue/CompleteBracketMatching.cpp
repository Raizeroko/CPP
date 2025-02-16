#include "Stack&Queue.h"

// Nowcoder
// MySolution
int main() {
    string s;
    while (cin >> s) { // 注意 while 处理多个 case
        stack<char> st;
        for (auto c : s) {
            if (c == ']' && !st.empty() && st.top() == '[') {
                st.pop();
            }
            else {
                st.push(c);
            }
        }
        int leftBucket = 0;
        int rightBucket = 0;
        while (!st.empty()) {
            if (st.top() == '[') leftBucket++;
            else rightBucket++;
            st.pop();
        }
        // cout << leftBucket << rightBucket;
        s.insert(0, rightBucket, '[');
        s.insert(s.size(), leftBucket, ']');
        cout << s;

    }
}
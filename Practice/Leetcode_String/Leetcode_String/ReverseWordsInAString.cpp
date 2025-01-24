# include "String.h"

// MySolution
class Solution {
public:
    string reverseWords(string s) {
        stack<string> st;
        string tmp = "";
        for (auto c : s) {
            if (c == ' ') {
                if (tmp != "")
                    st.push(tmp);
                tmp = "";
                continue;
            }
            tmp += c;
        }
        if (tmp != "")
            st.push(tmp);
        string ret;
        while (!st.empty()) {
            ret += st.top();
            if (st.size() != 1) {
                ret += ' ';
            }
            st.pop();
        }
        return ret;
    }
};
#include "String.h"

// MySolution
class Solution {
public:
    string reverseParentheses(string s) {
        string ret;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ')') {
                string tmp;
                while (ret.back() != '(') {
                    tmp += ret.back();
                    ret.pop_back();
                }
                ret.pop_back();
                ret += tmp;
                continue;
            }
            ret += s[i];
        }
        return ret;
    }
};
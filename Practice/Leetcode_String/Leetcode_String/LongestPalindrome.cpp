#include "String.h"

// MySolution
class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> harsh;
        for (auto c : s) {
            harsh[c]++;
        }
        int ret = 0;
        for (auto pair : harsh) {
            int value = pair.second;
            ret += value / 2 * 2;
            if (value % 2 == 1 and ret % 2 == 0)
                ret++;
        }
        return ret;
    }
};
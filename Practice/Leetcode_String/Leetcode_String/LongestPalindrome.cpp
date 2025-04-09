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

// Review 2025/04/09
class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> harsh;
        for (auto ch : s) {
            harsh[ch]++;
        }
        int max_odd = 0;
        int ret = 0;
        int flag = false;
        for (auto kv : harsh) {
            if (kv.second % 2 == 0) ret += kv.second;
            else {
                ret += kv.second - 1;
                flag = true;
            }
        }
        if (flag) ret += 1;
        return ret;
    }
};
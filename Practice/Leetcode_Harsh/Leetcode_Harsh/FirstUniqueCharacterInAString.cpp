#include "Harsh.h"

// MySolution
class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> harsh;
        for (auto c : s) {
            harsh[c]++;
        }
        for (int i = 0; i < s.size(); i++) {
            if (harsh[s[i]] == 1) {
                return i;
            }
        }
        return -1;
    }
};
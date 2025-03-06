#include "Vector.h"

// MySolution
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> harsh;
        int ret = 0;
        for (int l = 0, r = 0; r < s.size(); r++) {

            while (harsh.count(s[r])) {
                harsh.erase(s[l]);
                l++;
            }
            harsh.insert(s[r]);
            ret = max(ret, r - l + 1);
        }
        return ret;
    }
};
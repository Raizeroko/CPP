#include "String.h"

// MySolution
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> harshs, harsht;
        string ret;
        for (auto c : t) harsht[c]++;
        int left = 0;
        int right = 0;
        int count = 0;
        while (right < s.size()) {
            harshs[s[right]]++;
            if (harshs[s[right]] <= harsht[s[right]])  count++;
            while (harshs[s[left]] > harsht[s[left]]) {
                harshs[s[left]]--;
                left++;
            }
            if (count == t.size()) {
                if (ret.empty() || right - left + 1 < ret.size()) {
                    ret = s.substr(left, right - left + 1);
                }
            }
            right++;
        }
        return ret;
    }
};
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


// Review 2025/03/26
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> harsh;
        for (auto ch : t) {
            harsh[ch]++;
        }
        int len = s.size();
        int diff = harsh.size();
        int min_len = len + 1;
        int ans_l = -1;
        int l = 0, r = 0;
        while (r < len) {
            if (harsh.count(s[r]) && --harsh[s[r]] == 0) {
                diff--;
            }
            while (diff == 0 && l <= r) {
                if (min_len > r - l + 1) {
                    min_len = r - l + 1;
                    ans_l = l;
                }
                if (harsh.count(s[l]) && ++harsh[s[l]] > 0) {
                    diff++;
                }
                l++;
            }
            r++;
        }
        return min_len < len + 1 ? s.substr(ans_l, min_len) : "";
    }
};
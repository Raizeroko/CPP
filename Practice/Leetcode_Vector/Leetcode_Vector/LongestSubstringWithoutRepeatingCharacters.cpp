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

// Review 2025/09/11
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int left = 0;
        int right = 0;
        int ret = 0;
        unordered_map<char, int> harsh;
        while (right < s.size()) {
            harsh[s[right]]++;
            while (harsh[s[right]] > 1) {
                harsh[s[left]]--;
                left++;
            }
            ret = max(ret, right - left + 1);
            right++;
        }
        return ret;
    }
};
#include "harsh.h"

// MySolution
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> mp;
        for (auto ch : s) mp[ch]++;
        sort(s.begin(), s.end(), [&](const char& a, const char& b) {
            return mp[a] == mp[b] ? a > b : mp[a] > mp[b];
            });
        return s;
    }
};


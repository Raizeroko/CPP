#include "harsh.h"

// MySolution
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> mp;
        int length = s.length();
        for (auto& ch : s) {
            mp[ch]++;
        }
        vector<pair<char, int>> vec;
        for (auto& it : mp) {
            vec.emplace_back(it);
        }
        sort(vec.begin(), vec.end(), [](const pair<char, int>& a, const pair<char, int>& b) {
            return a.second > b.second;
            });
        string ret;
        for (auto& [ch, num] : vec) {
            for (int i = 0; i < num; i++) {
                ret.push_back(ch);
            }
        }
        return ret;
    }
};


// OptimSolution
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


// Review (2025_01_08)
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> harsh;
        for (auto c : s) harsh[c]++;
        sort(s.begin(), s.end(), [&](char& a, char& b) {
            return harsh[a] == harsh[b] ? a > b : harsh[a] > harsh[b];
            });
        return s;
    }
};



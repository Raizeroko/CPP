#include "string.h"

// MySolution
class Solution {
public:
    bool isAnagram(string s, string t) {
        unordered_map<char, int> map;
        for (auto c : s) {
            map[c]++;
        }
        for (auto c : t) {
            if (map.count(c)) {
                map[c]--;
            }
            else {
                return false;
            }
        }
        for (auto pair : map) {
            if (pair.second != 0) {
                return false;
            }
        }
        return true;
    }
};
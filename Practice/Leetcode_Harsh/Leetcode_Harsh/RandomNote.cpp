#include "Harsh.h"

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        std::unordered_map<char, int> mag;
        for (auto& e : magazine) {
            mag[e]++;
        }
        for (auto& note : ransomNote) {
            int& cur = mag[note];
            if (cur == 0) {
                return false;
            }
            cur--;
        }
        return true;
    }
};
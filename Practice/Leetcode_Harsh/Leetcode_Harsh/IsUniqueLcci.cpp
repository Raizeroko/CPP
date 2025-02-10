#include "Harsh.h"

// MySolution
class Solution {
public:
    bool isUnique(string astr) {
        unordered_set<char> harsh;
        for (auto c : astr) {
            if (harsh.count(c) == 0) {
                harsh.insert(c);
            }
            else {
                return false;
            }
        }
        return true;
    }
};
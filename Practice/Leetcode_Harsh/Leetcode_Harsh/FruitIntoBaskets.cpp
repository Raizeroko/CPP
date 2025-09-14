#include "Harsh.h"

// MySolution
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        unordered_map<int, int> classes;
        int l = 0;
        int r = 0;
        int ret = 0;
        for (; r < fruits.size(); r++) {
            classes[fruits[r]]++;
            while (classes.size() > 2) {
                classes[fruits[l]]--;
                if (classes[fruits[l]] == 0) classes.erase(fruits[l]);
                l++;
            }
            ret = max(ret, r - l + 1);
        }
        return ret;
    }
};
#include "DP.h"

// MySolution
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (auto num : nums) {
            sum += num;
        }
        if (sum % 2 != 0) {
            return false;
        }
        int half = sum / 2;
        unordered_set<int> harsh;
        for (auto num : nums) {
            vector<int> toHarsh;
            toHarsh.push_back(num);
            for (auto before : harsh) {
                if (before == half) {
                    return true;
                }
                int tmp = before + num;
                if (tmp == half) {
                    return true;
                }
                else if (tmp < half) {
                    toHarsh.push_back(tmp);
                }
            }
            for (auto insert : toHarsh) {
                harsh.insert(insert);
            }
        }
        return false;

    }
};

//
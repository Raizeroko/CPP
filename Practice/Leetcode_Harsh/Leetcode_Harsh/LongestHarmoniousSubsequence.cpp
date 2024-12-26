#include "harsh.h"

// MySolution
class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++) {
            if (map.find(nums[i]) == map.end()) {
                map[nums[i]] = 1;
            }
            else {
                map[nums[i]]++;
            }
        }
        int ret = 0;
        for (auto pair : map) {
            auto bound = map.find(pair.first + 1);
            if (bound != map.end())
                ret = max(ret, pair.second + bound->second);
        }
        return ret;
    }
};


// Optim with map->count()
class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++) {
            if (map.find(nums[i]) == map.end()) {
                map[nums[i]] = 1;
            }
            else {
                map[nums[i]]++;
            }
        }
        int ret = 0;
        for (auto pair : map) {
            if (map.count(pair.first + 1))
                ret = max(ret, pair.second + map[pair.first + 1]);
        }
        return ret;
    }
};
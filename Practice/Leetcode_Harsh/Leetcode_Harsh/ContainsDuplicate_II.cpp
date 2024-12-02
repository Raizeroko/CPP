#include<unordered_map>

using namespace std;

// MySolution
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> set;
        for (auto e : nums) {
            auto find = set.find(e);
            if (find != set.end()) {
                if (find->second <= k) {
                    return true;
                }
                find->second = 0;
            }
            else {
                set[e] = 0;
            }
            for (auto& f : set) {
                f.second++;
            }
        }
        return false;
    }

};

// OptimSolution
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++) {
            auto find = map.find(nums[i]);
            if (find != map.end() && i - find->second <= k) {
                return true;
            }
            map[nums[i]] = i;
        }
        return false;
    }
};
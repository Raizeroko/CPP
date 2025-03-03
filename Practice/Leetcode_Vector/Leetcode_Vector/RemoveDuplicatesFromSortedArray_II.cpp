#include "Vector.h"

// MySolution
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        unordered_map<int, int> harsh;
        auto it = nums.begin();
        while (it != nums.end()) {
            int& map = harsh[*it];
            if (map > 1) {
                it = nums.erase(it);
            }
            else {
                map++;
                it++;
            }

        }
        return nums.size();
    }
};

// OptimSolution
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        deque<int> dq;
        int prev = nums[0];
        for (auto num : nums) {
            if (dq.size() < 2) {
                dq.push_back(num);

            }
            else if (num != prev) {
                prev = dq.back();
                dq.push_back(num);
            }
        }
        int i = 0;
        while (!dq.empty()) {
            nums[i] = dq.front();
            dq.pop_front();
            i++;
        }
        return i;
    }
};

// OptimSolution
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() < 2) {
            return nums.size();
        }
        int slow = 2;
        int fast = slow;
        while (fast < nums.size()) {
            if (nums[slow - 2] != nums[fast]) {
                nums[slow] = nums[fast];
                slow++;
            }
            fast++;
        }
        return slow;
    }
};

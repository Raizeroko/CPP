#include "Vector.h"

// MySolution
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> v;
        for (int i = 0; i < nums1.size(); i++) {
            int j = 0;
            while (j < nums2.size() && nums1[i] != nums2[j]) {
                j++;
            }
            while (j < nums2.size()) {
                if (nums1[i] < nums2[j]) {
                    v.push_back(nums2[j]);
                    break;
                }
                j++;
            }
            if (j == nums2.size()) {
                v.push_back(-1);
            }
        }
        return v;
    }
};


// OptimSolution
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> map;
        stack<int> s;
        int i = nums2.size() - 1;
        while (i >= 0) {
            while (!s.empty() && nums2[i] > s.top()) {
                s.pop();
            }
            map[nums2[i]] = s.empty() ? -1 : s.top();
            s.push(nums2[i]);
            i--;
        }
        vector<int> ret;
        for (auto num : nums1) {
            ret.push_back(map[num]);
        }
        return ret;
    }
};
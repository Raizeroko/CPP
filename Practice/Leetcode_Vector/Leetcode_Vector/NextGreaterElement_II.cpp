#include "Vector.h"

// MySolution
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int maxi = 0;
        int max = nums[0];
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] > max) {
                max = nums[i];
                maxi = i;
            }
        }
        stack<int> s;
        vector<int> v(nums.size(), -1);
        int i = (maxi == 0 ? nums.size() : maxi) - 1;
        s.push(max);
        while (i != maxi) {
            while (!s.empty() && nums[i] >= s.top()) {
                s.pop();
            }
            if (!s.empty())
                v[i] = s.top();
            s.push(nums[i]);
            i--;
            if (i == -1) {
                i = nums.size() - 1;
            }
        }
        return v;
    }
};
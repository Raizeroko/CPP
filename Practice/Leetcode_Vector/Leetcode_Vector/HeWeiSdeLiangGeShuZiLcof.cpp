#include "Vector.h"

// MySolution
class Solution {
public:
    vector<int> twoSum(vector<int>& price, int target) {
        int left = 0;
        int right = price.size() - 1;
        vector<int> ret;
        while (left < right) {
            if (price[left] + price[right] < target) {
                left++;
            }
            else if (price[left] + price[right] > target) {
                right--;
            }
            else if (price[left] + price[right] == target) {
                ret.push_back(price[left]);
                ret.push_back(price[right]);
                return ret;
            }
        }
        return ret;
    }
};
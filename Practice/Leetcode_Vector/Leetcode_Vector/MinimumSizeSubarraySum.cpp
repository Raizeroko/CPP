#include <vector>
#include <queue>

using namespace std;

// MySolution
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        queue<int> q;
        int tmp = 0;
        int ret = nums.size() + 1;
        int i = 0;
        for (int i = 0; i < nums.size(); i++) {
            tmp += nums[i];
            q.push(nums[i]);
            while (!q.empty() && tmp >= target) {
                if (q.size() < ret) {
                    ret = q.size();
                }
                tmp -= q.front();
                q.pop();
            }
        }
        while (tmp >= target) {
            tmp -= q.front();
            q.pop();
            if (q.size() <= ret) {
                ret = q.size();
            }
        }
        if (ret == nums.size() + 1) {
            return 0;
        }
        return ret;
    }
};
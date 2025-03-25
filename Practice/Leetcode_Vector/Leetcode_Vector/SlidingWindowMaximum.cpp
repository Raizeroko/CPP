#include "Vector.h"

// MySolution
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> ret;
        priority_queue<pair<int, int>> pq;
        int right = 0;
        while (right < k) {
            pq.push(make_pair(nums[right], right));
            right++;
        }
        ret.push_back(pq.top().first);
        int left = 0;
        while (right < nums.size()) {
            pq.push(make_pair(nums[right], right));
            while (pq.top().second <= left)  pq.pop();
            ret.push_back(pq.top().first);
            right++;
            left++;
        }
        return ret;
    }
};


// OptimSolution
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> q;
        vector<int> ret;
        int right = 0;
        while (right < k) {
            while (!q.empty() && nums[right] >= nums[q.back()]) q.pop_back();
            q.push_back(right);
            right++;
        }
        ret.push_back(nums[q.front()]);
        int left = 0;
        while (right < nums.size()) {
            while (!q.empty() && nums[right] >= nums[q.back()]) q.pop_back();
            q.push_back(right);
            while (q.front() <= left) q.pop_front();
            ret.push_back(nums[q.front()]);
            left++;
            right++;
        }
        return ret;
    }
};
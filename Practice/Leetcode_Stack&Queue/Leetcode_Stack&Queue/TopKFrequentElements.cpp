#include "Stack&Queue.h"

// MySolution
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        if (nums.size() <= 1) return nums;
        sort(nums.begin(), nums.end());
        priority_queue<pair<int, int>> heap;
        int frequency = 0;
        for (int i = 0; i < nums.size() - 1; i++) {
            frequency++;
            if (nums[i] != nums[i + 1]) {
                heap.push(make_pair(frequency, nums[i]));
                cout << frequency << endl;
                frequency = 0;
            }
        }
        cout << frequency;
        heap.push(make_pair(frequency, nums.back()));
        vector<int> ret;
        while (!heap.empty() && k--) {
            ret.push_back(heap.top().second);
            heap.pop();
        }
        return ret;
    }
};
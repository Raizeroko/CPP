#include "DP.h"

// MySolution
class Solution {
public:
    int count(deque<int> pool) {
        int l = 0;
        int r = pool.size() - 1;
        while (pool[l + 1] > pool[r]) {
            l++;
        }
        while (pool[r - 1] > pool[l]) {
            r--;
        }
        int warter = min(pool[l], pool[r]) * (r - l - 1);
        int min = pool[l];
        for (int i = l + 1; i < r; i++) {
            if (pool[i] < min) {
                min = pool[i];
            }
            warter -= pool[i];
        }
        return warter;
    }

    int trap(vector<int>& height) {

        int ret = 0;
        int cur = 1;

        while (cur < height.size()) {
            deque<int> pool = {};
            while (height[cur] < height[cur + 1]) {
                cur++;
            }
            // left
            while (height[cur] > height[cur + 1]) {
                pool.push_back(height[cur]);
                cur++;
            }
            // right
            while (height[cur] < height[cur + 1]) {
                pool.push_back(height[cur]);
                cur++;
            }
            pool.push_back(height[cur]);
            // count 
            ret += count(pool);
            while (pool.size() > 1) {
                pool.pop_front();
            }
        }
        return ret;
    }
};


// OptimSolution
class Solution {
public:
    int trap(vector<int>& height) {
        int maxHeight = 0;
        int maxHeightPos = -1;
        for (int i = 0; i < height.size(); i++) {
            if (height[i] > maxHeight) {
                maxHeight = height[i];
                maxHeightPos = i;
            }
        }
        if (maxHeightPos == -1) return 0;
        int waterHeight = 0;
        int waterSum = 0;
        for (int i = 0; i < maxHeightPos; i++) {
            // 左侧水位
            if (height[i] > waterHeight) waterHeight = height[i];
            waterSum += waterHeight - height[i];
        }
        waterHeight = 0;
        for (int i = height.size() - 1; i > maxHeightPos; i--) {
            // 右侧水位
            if (height[i] > waterHeight) waterHeight = height[i];
            waterSum += waterHeight - height[i];
        }
        return waterSum;
    }
};


// OptimSolution
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int> leftMax(n);
        vector<int> rightMax(n);
        leftMax[0] = height[0];
        rightMax[n - 1] = height[n - 1];
        for (int i = 1; i < n; i++) {
            leftMax[i] = max(leftMax[i - 1], height[i]);
        }
        for (int i = n - 2; i >= 0; i--) {
            rightMax[i] = max(rightMax[i + 1], height[i]);
        }
        int warter = 0;
        for (int i = 0; i < n; i++) {
            warter += min(leftMax[i], rightMax[i]) - height[i];
        }
        return warter;
    }
};
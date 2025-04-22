#include "Puzzle.h"

//
class Solution {
    int jump(vector<int>& nums) {
        // 记录当前能跳跃到的位置的边界下标
        int border = 0;
        // 记录在边界范围内，能跳跃的最远位置的下标
        int maxPosition = 0;
        // 记录所用步数
        int steps = 0;
        for (int i = 0; i < nums.size() - 1; i++) {
            // 继续往下遍历，统计边界范围内，哪一格能跳得更远，每走一步就更新一次能跳跃的最远位置下标
            // 其实就是在统计下一步的最优情况
            maxPosition = max(maxPosition, nums[i] + i);
            // 如果到达了边界，那么一定要跳了，下一跳的边界下标就是之前统计的最优情况maxPosition，并且步数加1
            if (i == border) {
                border = maxPosition;
                steps++;
            }
        }
        return steps;
    }
};
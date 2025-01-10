#include "Puzzle.h"

// MySolution
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        // sumCost[i].first: one step to i
        // sumCost[i].second: two step to i
        vector<pair<int, int>> sumCost(cost.size() + 1);
        sumCost[0] = make_pair(0, 0);
        sumCost[1] = make_pair(0, 0);
        for (int i = 2; i < cost.size() + 1; i++) {
            sumCost[i].first = min(sumCost[i - 1].first, sumCost[i - 1].second) + cost[i - 1];
            sumCost[i].second = min(sumCost[i - 2].first, sumCost[i - 2].second) + cost[i - 2];
        }
        return min(sumCost.back().first, sumCost.back().second);
    }
};
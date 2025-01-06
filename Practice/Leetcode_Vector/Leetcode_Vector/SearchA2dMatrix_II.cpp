#include "Vector.h"

// MySolution
class Solution {
public:
    bool findTargetIn2DPlants(vector<vector<int>>& plants, int target) {
        if (plants.empty())  return false;
        int i = 0, j = plants[0].size() - 1;
        while (i < plants.size() && j >= 0) {
            if (plants[i][j] == target)  return true;
            else if (plants[i][j] > target) j--;
            else i++;
        }
        return false;
    }
};
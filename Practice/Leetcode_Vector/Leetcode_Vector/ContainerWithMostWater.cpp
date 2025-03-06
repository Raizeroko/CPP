#include "Vector.h"

// MySolution(58/65)
class Solution {
public:
     int maxArea(vector<int>& height) {
         int slow = 0;
         int fast = 1;
         int maxVolume = 0;
         while(fast < height.size()){
             int curVolume = min(height[slow], height[fast])*(fast-slow);
             if(curVolume > maxVolume){
                 maxVolume = curVolume;
                 int moveSlow = slow + 1;
                 while(moveSlow < fast){
                     int moveVolume = min(height[moveSlow], height[fast])*(fast-moveSlow);
                     if(moveVolume > maxVolume){
                         maxVolume = curVolume;
                         slow = moveSlow;
                     }
                     moveSlow++;
                 }
             }
             else{
                 fast++;
             }
         }
         return maxVolume;


     }
};

// OptimSolution
class Solution {
public:
    int maxArea(vector<int>& height) {
        int slow = 0;
        int fast = height.size() - 1;
        int maxVolume = 0;
        while (slow < fast) {
            int curVolume = min(height[slow], height[fast]) * (fast - slow);
            maxVolume = max(curVolume, maxVolume);
            if (height[slow] <= height[fast]) {
                slow++;
            }
            else {
                fast--;
            }
        }
        return maxVolume;
    }
};
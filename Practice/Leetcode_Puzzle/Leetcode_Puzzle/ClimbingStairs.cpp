
// MySolution
class Solution {
public:
    int climbStairs(int n) {
        int step[2] = { 1, 2 };
        if (n <= 2) {
            return step[n - 1];
        }
        else {
            while (n-- > 2) {
                int tmp = step[0] + step[1];
                step[0] = step[1];
                step[1] = tmp;
            }
        }
        return step[1];
    }
};
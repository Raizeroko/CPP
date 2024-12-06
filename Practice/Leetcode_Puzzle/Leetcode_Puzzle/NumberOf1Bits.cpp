
// MySolution
class Solution {
public:
    int hammingWeight(int n) {
        int ret = 0;
        while (n) {
            if (n & 1) {
                ret++;
            }
            n = n >> 1;
        }
        return ret;
    }
};
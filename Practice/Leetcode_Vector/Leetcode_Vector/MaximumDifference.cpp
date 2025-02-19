#include "Vector.h"

// Nowcoder
// MySolution
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param A int整型vector
     * @param n int整型
     * @return int整型
     */
    int getDis(vector<int>& A, int n) {
        // write code here
        int minLeft = -1;
        int max = 0;
        for (auto num : A) {
            if (minLeft == -1 || minLeft > num) {
                minLeft = num;
            }
            else {
                int sub = num - minLeft;
                if (sub > max) {
                    max = sub;
                }
            }
        }
        return max;
    }
};
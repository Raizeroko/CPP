#include "DP.h"

// Nowcoder
// MySolution
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param A string字符串
     * @return int整型
     */
    int getLongestPalindrome(string A) {
        int length = A.size();
        vector<vector<int>> v(length, vector<int>(length, 0));
        int ret = 0;
        for (int subLength = 0; subLength < length; subLength++) {
            for (int begin = 0; begin + subLength < length; begin++) {
                int end = begin + subLength;
                if (end - begin == 0) {
                    v[begin][end] = 1;
                }
                else if (end - begin == 1) {
                    v[begin][end] = (A[begin] == A[end]);
                }
                else {
                    v[begin][end] = (A[begin] == A[end]) && v[begin + 1][end - 1];
                }
                if (v[begin][end] && subLength + 1 > ret) {
                    ret = subLength + 1;
                }
            }
        }
        return ret;
    }
};
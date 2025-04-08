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

// Leetcode
// Review 2025/04/08
class Solution {
public:
    string longestPalindrome(string s) {
        int len = s.size();
        vector<vector<bool>> dp(len, vector<bool>(len, false));
        string ret;
        // 遍历顺序调整，确保 dp[i+1][j-1] 已经计算过
        for (int i = len - 1; i >= 0; i--) {
            for (int j = i; j < len; j++) {
                if (s[i] == s[j] && (j - i <= 1 || dp[i + 1][j - 1])) {
                    dp[i][j] = true;
                    if (j - i + 1 > ret.size()) {
                        ret = s.substr(i, j - i + 1);
                    }
                }
            }
        }
        return ret;
    }
};
#include "DP.h"

// Nowcoder
// MySolution
class Solution {
public:
    /**
     * �����е����������������������Ѿ�ָ���������޸ģ�ֱ�ӷ��ط����涨��ֵ����
     *
     *
     * @param A string�ַ���
     * @return int����
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
        // ����˳�������ȷ�� dp[i+1][j-1] �Ѿ������
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
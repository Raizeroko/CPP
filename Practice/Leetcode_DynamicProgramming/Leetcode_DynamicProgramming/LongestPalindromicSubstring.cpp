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
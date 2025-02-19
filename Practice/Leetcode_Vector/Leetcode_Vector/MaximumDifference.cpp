#include "Vector.h"

// Nowcoder
// MySolution
class Solution {
public:
    /**
     * �����е����������������������Ѿ�ָ���������޸ģ�ֱ�ӷ��ط����涨��ֵ����
     *
     *
     * @param A int����vector
     * @param n int����
     * @return int����
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
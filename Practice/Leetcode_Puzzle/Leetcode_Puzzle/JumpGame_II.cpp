#include "Puzzle.h"

//
class Solution {
    int jump(vector<int>& nums) {
        // ��¼��ǰ����Ծ����λ�õı߽��±�
        int border = 0;
        // ��¼�ڱ߽緶Χ�ڣ�����Ծ����Զλ�õ��±�
        int maxPosition = 0;
        // ��¼���ò���
        int steps = 0;
        for (int i = 0; i < nums.size() - 1; i++) {
            // �������±�����ͳ�Ʊ߽緶Χ�ڣ���һ�������ø�Զ��ÿ��һ���͸���һ������Ծ����Զλ���±�
            // ��ʵ������ͳ����һ�����������
            maxPosition = max(maxPosition, nums[i] + i);
            // ��������˱߽磬��ôһ��Ҫ���ˣ���һ���ı߽��±����֮ǰͳ�Ƶ��������maxPosition�����Ҳ�����1
            if (i == border) {
                border = maxPosition;
                steps++;
            }
        }
        return steps;
    }
};
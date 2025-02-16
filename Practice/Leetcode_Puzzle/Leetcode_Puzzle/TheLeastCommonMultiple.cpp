#include "Puzzle.h"

// �������Լ��
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// ������С������
int lcm(int a, int b) {
    return a / gcd(a, b) * b;  // �ȳ��ٳˣ��������
}

int main() {
    vector<int> nums(5);

    // ���������ͬ��������
    for (int i = 0; i < 5; ++i) {
        cin >> nums[i];
    }

    int result = INT_MAX;

    // ö�����е���Ԫ���
    for (int i = 0; i < 5; ++i) {
        for (int j = i + 1; j < 5; ++j) {
            for (int k = j + 1; k < 5; ++k) {
                // ����nums[i], nums[j], nums[k]��LCM
                int current_lcm = lcm(nums[i], lcm(nums[j], nums[k]));
                result = min(result, current_lcm);
            }
        }
    }

    // �����С���ڱ���
    cout << result << endl;

    return 0;
}

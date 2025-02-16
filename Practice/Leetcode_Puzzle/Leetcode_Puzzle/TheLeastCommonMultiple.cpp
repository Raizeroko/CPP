#include "Puzzle.h"

// 计算最大公约数
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// 计算最小公倍数
int lcm(int a, int b) {
    return a / gcd(a, b) * b;  // 先除再乘，避免溢出
}

int main() {
    vector<int> nums(5);

    // 输入五个不同的正整数
    for (int i = 0; i < 5; ++i) {
        cin >> nums[i];
    }

    int result = INT_MAX;

    // 枚举所有的三元组合
    for (int i = 0; i < 5; ++i) {
        for (int j = i + 1; j < 5; ++j) {
            for (int k = j + 1; k < 5; ++k) {
                // 计算nums[i], nums[j], nums[k]的LCM
                int current_lcm = lcm(nums[i], lcm(nums[j], nums[k]));
                result = min(result, current_lcm);
            }
        }
    }

    // 输出最小的众倍数
    cout << result << endl;

    return 0;
}

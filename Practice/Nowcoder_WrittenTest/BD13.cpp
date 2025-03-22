#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;


// 点的旋转公式
// x'= x1 + (x2-x1)cosθ - (y2-y1)sinθ
// y'= x1 + (x2-x1)cosθ + (y2-y1)sinθ

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        double x1, y1, x2, y2, x3, y3, x4, y4;
        cin >> x1 >> y1 >> x2 >> y2;

        // 计算向量AB
        double dx = x2 - x1, dy = y2 - y1;

        // 计算第一个可能的第三点坐标
        x3 = x1 + 0.5 * dx + sqrt(3) / 2 * dy;
        y3 = y1 - sqrt(3) / 2 * dx + 0.5 * dy;

        // 计算第二个可能的第三点坐标
        x4 = x1 + 0.5 * dx - sqrt(3) / 2 * dy;
        y4 = y1 + sqrt(3) / 2 * dx + 0.5 * dy;

        // 按坐标值从小到大输出
        if (x3 < x4 || (x3 == x4 && y3 <= y4)) {
            cout << fixed << setprecision(2)
                 << x3 << " " << y3 << " "
                 << x4 << " " << y4 << endl;
        } else {
            cout << fixed << setprecision(2)
                 << x4 << " " << y4 << " "
                 << x3 << " " << y3 << endl;
        }
    }
    return 0;
}

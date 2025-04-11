#include "directory_scanner.h"
#include <string>
#include <iostream>


int main() {
    std::string target_path = "C:\\windows";
    Scanner scanner;

    // 记录开始时间
    auto start_time = std::chrono::high_resolution_clock::now();

    scanner.Scan(target_path);

    // 记录结束时间
    auto end_time = std::chrono::high_resolution_clock::now();

    // 计算总时间（以毫秒为单位）
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    // 输出扫描结果
    std::cout << "Total Size: " << scanner.Size() / 1024 << " KB" << std::endl;
    std::cout << "Elapsed Time: " << duration << " ms" << std::endl;

    system("pause");
    return 0;
}
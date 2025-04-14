#include "scanner.h"
#include <string>
#include <iostream>

int main() {
    std::string target_path = "C:\\windows";
    Scanner scanner;

    // 记录开始时间
    auto start_time = std::chrono::high_resolution_clock::now();

    // 开始
    scanner.Scan(target_path);

    // 记录结束时间
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "文件总大小: " << scanner.Size() / 1024 << " KB" << std::endl;
    std::cout << "用时: " << duration << " ms" << std::endl;

    system("pause");
    return 0;
}
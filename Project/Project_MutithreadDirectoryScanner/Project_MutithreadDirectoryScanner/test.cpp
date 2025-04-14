#include "scanner.h"
#include <string>
#include <iostream>

int main() {
    std::string target_path = "C:\\windows";
    Scanner scanner;

    // ��¼��ʼʱ��
    auto start_time = std::chrono::high_resolution_clock::now();

    // ��ʼ
    scanner.Scan(target_path);

    // ��¼����ʱ��
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "�ļ��ܴ�С: " << scanner.Size() / 1024 << " KB" << std::endl;
    std::cout << "��ʱ: " << duration << " ms" << std::endl;

    system("pause");
    return 0;
}
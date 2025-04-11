#include "directory_scanner.h"
#include <string>
#include <iostream>


int main() {
    std::string target_path = "C:\\windows";
    Scanner scanner;

    // ��¼��ʼʱ��
    auto start_time = std::chrono::high_resolution_clock::now();

    scanner.Scan(target_path);

    // ��¼����ʱ��
    auto end_time = std::chrono::high_resolution_clock::now();

    // ������ʱ�䣨�Ժ���Ϊ��λ��
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    // ���ɨ����
    std::cout << "Total Size: " << scanner.Size() / 1024 << " KB" << std::endl;
    std::cout << "Elapsed Time: " << duration << " ms" << std::endl;

    system("pause");
    return 0;
}
#pragma once
#include <string>
#include <atomic>
#include <thread>
#include <mutex>
#include <filesystem>
#include <iostream>
#include <queue>
#include <condition_variable>
#include <vector>
#include <algorithm> 

namespace fs = std::filesystem;

class Scanner {
public:
    // 构造函数，初始化变量并创建工作线程
    Scanner()
        : _stop(false), _total_size(0), _active_workers(0) {
        // 获取硬件支持的最大线程数
        thread_count = std::thread::hardware_concurrency();
        if (thread_count == 0) {
            thread_count = 1; 
        }

        // 启动工作线程
        for (size_t i = 0; i < thread_count; ++i) {
            _threads.emplace_back(&Scanner::WorkerThread, this); 
        }
    }

    ~Scanner() {
        // 加锁并设置停止标志
        std::unique_lock<std::mutex> lock(_queue_mutex);
        _stop = true;
        lock.unlock();  
        // 释放锁后通知所有线程停止
        _cv.notify_all();  

        // 等待所有线程完成
        for (std::thread& thread : _threads) {
            if (thread.joinable()) {
                thread.join();  
            }
        }
    }

    // 执行扫描操作
    void Scan(const std::string& path) {
        // 加锁将任务路径放入任务队列
        std::unique_lock<std::mutex> lock(_queue_mutex);
        _task_queue.push(path);
        lock.unlock();  

        _cv.notify_all();

        WaitForCompletion();
    }

    uint64_t Size() const {
        return _total_size.load();
    }

private:
    // 工作线程执行的函数
    void WorkerThread() {
        while (true) {
            std::string task;

            // 等待并获取任务队列中的任务
            std::unique_lock<std::mutex> lock(_queue_mutex);
            _cv.wait(lock, [this] { return _stop || !_task_queue.empty(); });

            // 如果停止且任务队列为空，结束线程
            if (_stop && _task_queue.empty()) {
                return;
            }

            // 获取并移除队列中的任务
            task = std::move(_task_queue.front());
            _task_queue.pop();
            lock.unlock();  

            // 处理任务
            _active_workers++;  
            ProcessTask(task);
            _active_workers--;  

            _cv.notify_all();
        }
    }

    // 等待所有任务完成
    void WaitForCompletion() {
        std::unique_lock<std::mutex> lock(_queue_mutex);
        _cv.wait(lock, [this] { return _task_queue.empty() && _active_workers == 0; });
    }

    // 处理扫描任务，遍历文件夹并计算文件大小
    void ProcessTask(const std::string& path) {
        try {
            for (const auto& entry : fs::directory_iterator(path, fs::directory_options::skip_permission_denied)) {
                if (entry.is_directory()) {
                    // 目录
                    std::unique_lock<std::mutex> lock(_queue_mutex);
                    _task_queue.push(entry.path().string());
                    _cv.notify_all();  
                }
                else if (entry.is_regular_file()) {
                    // 文件
                    _total_size += entry.file_size();
                }
            }
        }
        catch (const fs::filesystem_error& e) {
            // 如果访问某个目录时出现错误，输出错误信息
            std::cerr << "路径错误" << path << ": " << e.what() << std::endl;
        }
    }

private:
    std::queue<std::string> _task_queue;    // 保存待扫描的目录路径
    std::mutex _queue_mutex;                // 保护任务队列
    std::condition_variable _cv;            // 线程同步
    std::atomic<uint64_t> _total_size;      // 扫描的总文件大小
    std::atomic<bool> _stop;                // 停止标志，用于停止所有线程
    std::atomic<size_t> _active_workers;    // 活跃工作线程的数量
    size_t thread_count;                    // 工作线程数量
    std::vector<std::thread> _threads;      // 存储工作线程的容器
};


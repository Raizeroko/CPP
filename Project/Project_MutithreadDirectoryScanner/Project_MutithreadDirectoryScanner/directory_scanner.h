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
#include <algorithm> // 用于std::max

namespace fs = std::filesystem;

class Scanner {
public:
    Scanner()
        : _stop(false), _total_size(0), _active_workers(0) {
        thread_count = std::thread::hardware_concurrency();
        if (thread_count == 0) {
            thread_count = 1;
        }
        for (size_t i = 0; i < thread_count; ++i) {
            _threads.emplace_back(&Scanner::WorkerThread, this);
        }
    }

    ~Scanner() {
        {
            std::unique_lock<std::mutex> lock(_queue_mutex);
            _stop = true;
        }
        _cv.notify_all();
        for (std::thread& thread : _threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    }

    void Scan(const std::string& path) {
        {
            std::unique_lock<std::mutex> lock(_queue_mutex);
            _task_queue.push(path);
        }
        _cv.notify_all();

        WaitForCompletion();
    }

    uint64_t Size() const {
        return _total_size.load();
    }

private:
    void WorkerThread() {
        while (true) {
            std::string task;
            {
                std::unique_lock<std::mutex> lock(_queue_mutex);
                _cv.wait(lock, [this] { return _stop || !_task_queue.empty(); });

                if (_stop && _task_queue.empty()) {
                    return;
                }

                task = std::move(_task_queue.front());
                _task_queue.pop();
            }

            _active_workers++;
            ProcessTask(task);
            _active_workers--;

            _cv.notify_all(); // 通知等待完成的主线程
        }
    }

    void WaitForCompletion() {
        std::unique_lock<std::mutex> lock(_queue_mutex);
        _cv.wait(lock, [this] { return _task_queue.empty() && _active_workers == 0; });
    }

    void ProcessTask(const std::string& path) {
        try {
            for (const auto& entry : fs::directory_iterator(path, fs::directory_options::skip_permission_denied)) {
                if (entry.is_directory()) {
                    std::unique_lock<std::mutex> lock(_queue_mutex);
                    _task_queue.push(entry.path().string());
                    _cv.notify_all(); // 通知其他线程有新任务
                }
                else if (entry.is_regular_file()) {
                    _total_size += entry.file_size(); // atomic操作，线程安全
                }
            }
        }
        catch (const fs::filesystem_error& e) {
            std::cerr << "Error accessing " << path << ": " << e.what() << std::endl;
        }
    }

private:
    std::queue<std::string> _task_queue;
    std::mutex _queue_mutex;
    std::condition_variable _cv;
    std::atomic<uint64_t> _total_size;
    std::atomic<bool> _stop;
    std::atomic<size_t> _active_workers;
    size_t thread_count;
    std::vector<std::thread> _threads;
};
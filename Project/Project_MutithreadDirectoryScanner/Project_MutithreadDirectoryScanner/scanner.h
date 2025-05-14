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
    // ���캯������ʼ�����������������߳�
    Scanner()
        : _stop(false), _total_size(0), _active_workers(0) {
        // ��ȡӲ��֧�ֵ�����߳���
        thread_count = std::thread::hardware_concurrency();
        if (thread_count == 0) {
            thread_count = 1; 
        }

        // ���������߳�
        for (size_t i = 0; i < thread_count; ++i) {
            _threads.emplace_back(&Scanner::WorkerThread, this); 
        }
    }

    ~Scanner() {
        // ����������ֹͣ��־
        std::unique_lock<std::mutex> lock(_queue_mutex);
        _stop = true;
        lock.unlock();  
        // �ͷ�����֪ͨ�����߳�ֹͣ
        _cv.notify_all();  

        // �ȴ������߳����
        for (std::thread& thread : _threads) {
            if (thread.joinable()) {
                thread.join();  
            }
        }
    }

    // ִ��ɨ�����
    void Scan(const std::string& path) {
        // ����������·�������������
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
    // �����߳�ִ�еĺ���
    void WorkerThread() {
        while (true) {
            std::string task;

            // �ȴ�����ȡ��������е�����
            std::unique_lock<std::mutex> lock(_queue_mutex);
            _cv.wait(lock, [this] { return _stop || !_task_queue.empty(); });

            // ���ֹͣ���������Ϊ�գ������߳�
            if (_stop && _task_queue.empty()) {
                return;
            }

            // ��ȡ���Ƴ������е�����
            task = std::move(_task_queue.front());
            _task_queue.pop();
            lock.unlock();  

            // ��������
            _active_workers++;  
            ProcessTask(task);
            _active_workers--;  

            _cv.notify_all();
        }
    }

    // �ȴ������������
    void WaitForCompletion() {
        std::unique_lock<std::mutex> lock(_queue_mutex);
        _cv.wait(lock, [this] { return _task_queue.empty() && _active_workers == 0; });
    }

    // ����ɨ�����񣬱����ļ��в������ļ���С
    void ProcessTask(const std::string& path) {
        try {
            for (const auto& entry : fs::directory_iterator(path, fs::directory_options::skip_permission_denied)) {
                if (entry.is_directory()) {
                    // Ŀ¼
                    std::unique_lock<std::mutex> lock(_queue_mutex);
                    _task_queue.push(entry.path().string());
                    _cv.notify_all();  
                }
                else if (entry.is_regular_file()) {
                    // �ļ�
                    _total_size += entry.file_size();
                }
            }
        }
        catch (const fs::filesystem_error& e) {
            // �������ĳ��Ŀ¼ʱ���ִ������������Ϣ
            std::cerr << "·������" << path << ": " << e.what() << std::endl;
        }
    }

private:
    std::queue<std::string> _task_queue;    // �����ɨ���Ŀ¼·��
    std::mutex _queue_mutex;                // �����������
    std::condition_variable _cv;            // �߳�ͬ��
    std::atomic<uint64_t> _total_size;      // ɨ������ļ���С
    std::atomic<bool> _stop;                // ֹͣ��־������ֹͣ�����߳�
    std::atomic<size_t> _active_workers;    // ��Ծ�����̵߳�����
    size_t thread_count;                    // �����߳�����
    std::vector<std::thread> _threads;      // �洢�����̵߳�����
};


#pragma once
#include <thread>
#include <vector>
#include <condition_variable>

#include "task.h"

const int MAX_THREAD = 10;

class ThreadPool {
private:
	void handleTask();
public:
	ThreadPool();
	void submitTask(Task* task);
	void shutDown();
	~ThreadPool();

private:
	TaskQueue task_queue_;
	std::vector<std::thread> thread_pool_;
	std::mutex mutex_;
	std::condition_variable empty_cv_;
	bool stop_;
};
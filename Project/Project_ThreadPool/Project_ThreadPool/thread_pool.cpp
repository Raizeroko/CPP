#include "thread_pool.h"

ThreadPool::ThreadPool() {
	stop_ = false;
	for (int i = 0; i < MAX_THREAD; i++) {
		thread_pool_.push_back(std::thread(&ThreadPool::handleTask, this));
	}
}

void ThreadPool::handleTask() {
	while (true) {
		Task* task = nullptr;
		{
			std::unique_lock<std::mutex> umutex(mutex_);
			empty_cv_.wait(umutex, [this]() {
				return stop_ || !task_queue_.empty();
				});
			if (stop_ && task_queue_.empty()) return;
			task = task_queue_.pop();
		}
		
		if (task) task->run();
	}
}

void ThreadPool::submitTask(Task* task) {
	{
		std::unique_lock<std::mutex> umutex(mutex_);
		task_queue_.push(task);
	}
	empty_cv_.notify_one();
}
void ThreadPool::shutDown() {
	{
		std::lock_guard<std::mutex> lock(mutex_);
		stop_ = true;
	}
	empty_cv_.notify_all();
	for (int i = 0; i < MAX_THREAD; i++) {
		thread_pool_[i].join();
	}
}
ThreadPool::~ThreadPool() {
	shutDown();
}


#pragma once
#include <queue>
#include <mutex>
#include <iostream>

class Task {
public:
	virtual void run() = 0;
	virtual ~Task() = default; 
};

class TaskAdd:public Task {
public:
	TaskAdd(int a, int b)
		:a_(a)
		,b_(b)
	{}
	virtual void run() override {
		int result = a_ + b_;
		std::cout << a_ << " + " << b_ << "=" << result << std::endl;

	}

private:
	int a_;
	int b_;
};


class TaskQueue {
public:
	void push(Task* task);
	bool empty();
	Task* pop();
private:
	std::queue<Task*> task_queue_;
	//std::mutex mutex_;
};
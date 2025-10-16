#include "task.h"

void TaskQueue::push(Task* task) {
	task_queue_.push(task);
}
bool TaskQueue::empty() {
	return task_queue_.empty();
}
Task* TaskQueue::pop() {
	if (task_queue_.empty()) return nullptr;
	Task* task = task_queue_.front();
	task_queue_.pop();
	return task;
}


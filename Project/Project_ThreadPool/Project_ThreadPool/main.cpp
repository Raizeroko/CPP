#include "thread_pool.h"

const int MAX_TASK = 10;

void test() {
	ThreadPool tp;
	for (int i = 0; i < MAX_TASK; i++) {
		Task* task = new TaskAdd(i, i + 1);
		tp.submitTask(task);
	}
	//tp.shutDown();
}
int main() {

	test();
}
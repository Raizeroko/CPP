#include "Stack&Queue.h"

// MySolution
class MyStack {
public:
    MyStack()
        :qPush(&queue1)
        , qPop(&queue2)
    {
    }

    void push(int x) {
        qPush->push(x);
        while (!qPop->empty()) {
            qPush->push(qPop->front());
            qPop->pop();
        }
        swap(qPush, qPop);
    }

    int pop() {
        int ret = top();
        qPop->pop();
        return ret;
    }

    int top() {
        return qPop->front();
    }

    bool empty() {
        return qPop->empty();
    }
private:
    queue<int> queue1;
    queue<int> queue2;
    queue<int>* qPush;
    queue<int>* qPop;
};
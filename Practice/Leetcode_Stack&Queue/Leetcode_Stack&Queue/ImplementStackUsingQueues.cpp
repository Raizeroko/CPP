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


// Review 2025/04/06
class MyStack {
    queue<int>* _qPush;
    queue<int>* _qPop;;
public:
    MyStack() {
        _qPush = new queue<int>;
        _qPop = new queue<int>;
    }

    void push(int x) {
        _qPush->push(x);
        while (!_qPop->empty()) {
            _qPush->push(_qPop->front());
            _qPop->pop();
        }
        swap(_qPush, _qPop);
    }

    int pop() {
        int tmp = -1;
        if (!_qPop->empty()) {
            tmp = _qPop->front();
            _qPop->pop();
        }
        return tmp;
    }

    int top() {
        return _qPop->front();
    }

    bool empty() {
        return _qPop->empty();
    }
};
#include <list>

using namespace std;

// MySolution
class MinStack {
public:
    MinStack() {
        _min = 0;
    }

    void push(int val) {
        if (_head.size() == 0) {
            _min = val;
        }
        _head.push_front(val);
        if (_min > val)
        {
            _min = val;
        }
    }

    void pop() {
        int front = _head.front();
        _head.pop_front();
        if (front == _min) {
            auto it = _head.begin();
            _min = _head.front();
            while (it != _head.end()) {
                if (*it < _min) {
                    _min = *it;
                }
                it++;
            }
        }
    }

    int top() {
        return _head.front();
    }

    int getMin() {
        return _min;
    }
private:
    list<int> _head;
    int _min;
};

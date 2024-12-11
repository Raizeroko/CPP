#include <stack>

using namespace std;

// MySolution
class MyQueue {
public:
    MyQueue()
    {}

    void push(int x) {
        sPush.push(x);
    }

    int pop() {
        int ret = peek();
        if (!empty())
            sPop.pop();
        return ret;
    }

    int peek() {
        if (!sPop.empty()) {
            return sPop.top();
        }
        if (sPop.empty() && !sPush.empty()) {
            pushToPop();
            return sPop.top();
        }
        return -1;
    }

    bool empty() {
        return sPush.empty() && sPop.empty();
    }
private:
    void pushToPop() {
        while (!sPush.empty()) {
            sPop.push(sPush.top());
            sPush.pop();
        }
    }

    stack<int>  sPush;
    stack<int>  sPop;
};
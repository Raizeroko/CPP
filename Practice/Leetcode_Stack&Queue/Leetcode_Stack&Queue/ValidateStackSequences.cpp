#include "stack"
#include "vector"

using namespace std;

// MySolution
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> s;
        int pushi = 0;
        int popi = 0;
        while (pushi != pushed.size()) {
            if (!s.empty() && s.top() == popped[popi]) {
                s.pop();
                popi++;
                continue;
            }
            s.push(pushed[pushi]);
            pushi++;
        }
        while (popi != popped.size()) {
            if (s.top() != popped[popi]) {
                return false;
            }
            s.pop();
            popi++;
        }
        return true;
    }
};

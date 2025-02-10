#include "Stack&Queue.h"


// MySolution
class Solution {
public:
    bool isSubsequence(string s, string t) {
        queue<char> q;
        for (auto e : s) {
            q.push(e);
        }
        for (auto e : t) {
            if (e == q.front()) {
                q.pop();
            }
        }
        if (q.empty()) {
            return true;
        }
        return false;
    }
};
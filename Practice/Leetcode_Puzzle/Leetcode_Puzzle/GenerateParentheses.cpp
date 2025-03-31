#include "Puzzle.h"

// MySolution
class Solution {
    vector<string> ret;
public:
    void dfs(int n, int level, string tmp, int back) {
        if (n == level) {
            if (back == 0) {
                ret.push_back(tmp);
            }
            return;
        }
        tmp += '(';
        back++;
        for (int i = 0; i <= back; i++) {
            dfs(n, level + 1, tmp, back - i);
            tmp += ')';
        }

    }

    vector<string> generateParenthesis(int n) {
        int level = 0;
        string tmp;
        int back = 0;
        dfs(n, level, tmp, back);
        return ret;
    }
};
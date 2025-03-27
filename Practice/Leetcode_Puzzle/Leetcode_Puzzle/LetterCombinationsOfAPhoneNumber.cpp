#include "Puzzle.h"

// MySolution
class Solution {
    vector<string> map = { "","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz" };
    vector<string> ret;
public:
    void dfs(const string& digits, int level, string path) {
        if (level == digits.size()) {
            ret.push_back(path);
            return;
        }
        for (auto ch : map[digits[level] - '0']) {
            path += ch;
            dfs(digits, level + 1, path);
            path.pop_back();
        }
    }


    vector<string> letterCombinations(string digits) {
        if (digits.size() == 0) return vector<string>();
        string path;
        dfs(digits, 0, path);
        return ret;
    }
};
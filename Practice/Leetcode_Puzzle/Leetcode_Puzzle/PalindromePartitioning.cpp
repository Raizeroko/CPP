#include "Puzzle.h"

// MySolution 
class Solution {
    vector<vector<string>> ret;
    vector<vector<bool>> isPalinrome;
public:
    void dfs(const string s, vector<string> tmp, int l) {
        if (l >= s.size()) {
            ret.push_back(tmp);
            return;
        }
        for (int r = l; r < s.size(); r++) {
            if (isPalinrome[l][r]) {
                tmp.push_back(s.substr(l, r - l + 1));
                dfs(s, tmp, r + 1);
                tmp.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s) {
        int len = s.size();
        isPalinrome = vector<vector<bool>>(len, vector<bool>(len, false));
        // i->j是否是一个回文串
        for (int i = len - 1; i >= 0; i--) {
            for (int j = i; j < len; j++) {
                if (i == j) isPalinrome[i][j] = true;
                if (s[i] == s[j] && (j - i <= 1 || isPalinrome[i + 1][j - 1])) {
                    isPalinrome[i][j] = true;
                }
            }
        }
        vector<string> tmp;
        dfs(s, tmp, 0);
        return ret;
    }
};


// OptimSolution
class Solution {
    vector<vector<string>> ret;
    vector<vector<bool>> isPalinrome;
    vector<string> tmp;

public:
    void dfs(const string s, int l) {
        if (l >= s.size()) {
            ret.emplace_back(tmp);
            return;
        }
        for (int r = l; r < s.size(); r++) {
            if (isPalinrome[l][r]) {
                tmp.emplace_back(s.substr(l, r - l + 1));
                dfs(s, r + 1);
                tmp.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s) {
        int len = s.size();
        isPalinrome = vector<vector<bool>>(len, vector<bool>(len, false));
        // i->j是否是一个回文串
        for (int i = len - 1; i >= 0; i--) {
            for (int j = i; j < len; j++) {
                if (i == j) isPalinrome[i][j] = true;
                if (s[i] == s[j] && (j - i <= 1 || isPalinrome[i + 1][j - 1])) {
                    isPalinrome[i][j] = true;
                }
            }
        }
        dfs(s, 0);
        return ret;
    }
};
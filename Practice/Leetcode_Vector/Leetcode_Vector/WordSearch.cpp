#include "vector.h"

// MySolution
class Solution {
    vector<vector<bool>> visited;
    const vector<pair<int, int>> nears{ {-1, 0}, {0,-1}, {0, 1}, {1, 0} };
    int m;
    int n;

public:
    bool IsValidLoc(pair<int, int> loc) {
        if (loc.first < 0 || loc.first >= m) return false;
        if (loc.second < 0 || loc.second >= n) return false;
        if (visited[loc.first][loc.second]) return false; // �Ѿ����ʹ�
        return true;
    }

    bool dfs(const vector<vector<char>>& board, const string& word, pair<int, int> loc, int cur) {
        // ��ǰ�ַ���ƥ�䣬���߳���Ŀ���ַ�������
        if (board[loc.first][loc.second] != word[cur]) return false;
        if (cur == word.size() - 1) return true;

        visited[loc.first][loc.second] = true; // ����ѷ���

        for (auto dir : nears) {
            pair<int, int> next = { loc.first + dir.first, loc.second + dir.second };
            if (IsValidLoc(next)) {
                if (dfs(board, word, next, cur + 1)) {
                    return true;
                }
            }
        }

        visited[loc.first][loc.second] = false; // ���ݣ��ָ�״̬
        return false;
    }

    bool exist(vector<vector<char>>& board, string word) {
        m = board.size();
        n = board[0].size();
        visited = vector<vector<bool>>(m, vector<bool>(n, false)); // ��ʼ�����ʱ��

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dfs(board, word, { i, j }, 0)) return true;
            }
        }
        return false;
    }
};

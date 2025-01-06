#include "string.h"

// MySolution(30/31) 超出时间限制
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_set<string> set;
        vector<string> vs;
        for (int i = 0; i <= (int)s.size() - 10 - 1; i++) {
            string substr = s.substr(i, 10);
            for (int j = i + 1; j <= s.size() - 10; j++) {
                if (s.compare(j, 10, substr) == 0) {
                    set.insert(substr);
                }
            }
        }
        vs = vector<string>(set.begin(), set.end());
        return vs;
    }
};


// OptimSolution
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<string, int> harsh;
        vector<string> vs;
        for (int i = 0; i <= (int)s.size() - 10; i++) {
            string substr = s.substr(i, 10);
            harsh[substr]++;
            if (harsh[substr] == 2) {
                vs.push_back(substr);
            }
        }
        return vs;
    }
};
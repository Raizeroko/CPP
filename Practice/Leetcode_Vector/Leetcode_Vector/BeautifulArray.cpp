#include "Vector.h"

// MySolution
class Solution {
public:
    vector<int> beautifulArray(int n) {
        if (n == 1) {
            return vector<int>(1, 1);
        }
        int left = (n + 1) / 2;
        int right = n / 2;
        vector<int> vleft = beautifulArray(left);
        vector<int> vright = beautifulArray(right);
        for (auto& num : vleft) {
            num = 2 * num - 1;
        }
        for (auto& num : vright) {
            num = 2 * num;
        }
        vleft.insert(vleft.end(), vright.begin(), vright.end());
        return vleft;
    }
};


// OptimSolution
class Solution {
public:
    unordered_map<int, vector<int>> harsh;
    vector<int> beautifulArray(int n) {
        if (n == 1) {
            harsh[n] = vector<int>(1, 1);
            return harsh[n];
        }
        if (harsh.find(n) != harsh.end()) {
            return harsh[n];
        }
        //left
        vector<int> v;
        for (auto num : beautifulArray((n + 1) / 2)) {
            v.push_back(num * 2 - 1);
        }
        for (auto num : beautifulArray(n / 2)) {
            v.push_back(num * 2);
        }
        harsh[n] = v;
        return harsh[n];
    }
};
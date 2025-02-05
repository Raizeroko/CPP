#include "Harsh.h"

// MySolution
class Solution {
public:
    bool isHappy(int n) {
        int flag = 0;
        while (n != 1) {
            int tmp = 0;
            while (n != 0) {
                tmp += pow(n % 10, 2);
                n /= 10;
            }
            flag++;
            n = tmp;
            if (flag == 8) {
                return false;
            }
        }
        return true;
    }
};


// OptimSolution
class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> harsh;
        harsh.insert(n);
        while (n != 1) {
            int tmp = 0;
            while (n != 0) {
                tmp += pow(n % 10, 2);
                n /= 10;
            }
            if (harsh.count(tmp) != 0) {
                return false;
            }
            harsh.insert(tmp);
            n = tmp;

        }
        return true;
    }
};
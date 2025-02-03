#include "String.h"

// MySolution
class Solution {
public:
    int lengthOfLastWord(string s) {
        int back = s.size() - 1;
        while (s[back] == ' ') {
            back--;
        }
        int length = 0;
        while (back >= 0 && s[back] != ' ') {
            back--;
            length++;
        }
        return length;
    }
};
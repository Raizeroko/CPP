#include "String.h"

// MySolution Unpass(460/466)
class Solution {
public:
    bool validPalindrome(string s) {
        int left = 0;
        int right = s.size() - 1;
        int flag = 1;
        while (left < right) {
            if (flag == 1 && s[left] != s[right]) {
                if (s[left + 1] == s[right]) {
                    flag = 0;
                    left++;
                }
                else if (s[left] == s[right - 1]) {
                    flag = 0;
                    right--;
                }
                else {
                    return false;
                }
                continue;
            }
            else if (flag == 0 && s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
};


// MySolution
class Solution {
public:
    bool _isPalindrome(string& s, int& left, int& right) {
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }

    bool validPalindrome(string s) {
        int left = 0;
        int right = s.size() - 1;
        _isPalindrome(s, left, right);
        int copyLeft = left;
        int copyRight = right;
        return _isPalindrome(s, ++left, right) || _isPalindrome(s, copyLeft, --copyRight);

    }
};
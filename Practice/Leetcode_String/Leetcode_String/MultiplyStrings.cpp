#include "String.h"

class Solution {
public:
    int mulChar(char c1, char c2, int& carry) {
        int i1 = c1 - '0';
        int i2 = c2 - '0';
        int result = i1 * i2 + carry;
        carry = result / 10;
        return result % 10;
    }

    string plusString(string string1, string string2) {
        string ret;
        int carry = 0;
        while (string1.size() < string2.size()) {
            string1 += '0';
        }
        for (int i = 0; i < string1.size(); i++) {
            int num1 = string1[i] - '0';
            int num2 = string2[i] - '0';
            int plus = num1 + num2 + carry;
            ret += plus % 10 + '0';
            carry = plus / 10;
        }
        if (carry != 0) {
            ret += carry + '0';
        }
        return ret;
    }

    string multiply(string num1, string num2) {
        string rnum1(num1.rbegin(), num1.rend());
        string rnum2(num2.rbegin(), num2.rend());
        string ret;
        for (int i = 0; i < rnum1.size(); i++) {
            int mul = 0;
            int carry = 0;
            string mulstring;
            for (int j = 0; j < rnum2.size(); j++) {
                mul = mulChar(rnum1[i], rnum2[j], carry);
                mulstring += mul + '0';
            }
            if (carry != 0) {
                mulstring += carry + '0';
            }
            for (int zero = i; zero > 0; zero--) {
                mulstring.insert(0, "0");
            }
            ret = plusString(ret, mulstring);
        }
        ret = string(ret.rbegin(), ret.rend());
        while (ret[0] == '0' && ret.size() > 1) {
            ret.erase(0, 1);
        }
        return ret;
    }
};



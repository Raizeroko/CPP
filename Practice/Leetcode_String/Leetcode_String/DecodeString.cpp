#include "String.h"

// MySolution
class Solution {
public:
    string decodeString(string s) {
        stack<int> st_num;
        deque<string> st_str;
        string tmp;
        int k = 0;
        for (auto e : s) {
            // Êý×Ö
            if (e >= '0' && e <= '9') {
                k = k * 10 + (e - '0');
            }
            // ×Ö·û
            else if (e >= 'a' && e <= 'z') {
                tmp += e;
            }
            // [
            else if (e == '[') {
                st_str.push_back(tmp);
                // cout << tmp << endl;
                st_num.push(k);
                k = 0;
                tmp = "";
            }
            // ]
            else if (e == ']') {
                string encoded_string = tmp;
                // cout << encoded_string << endl;
                // st_str.pop_back();
                // encoded_string += tmp;
                int k = st_num.top();
                st_num.pop();
                string decode_string = st_str.back();
                st_str.pop_back();
                for (int i = 0; i < k; i++) {
                    decode_string += encoded_string;
                }
                cout << decode_string << endl;
                tmp = decode_string;
            }
            else {
                break;
            }
        }
        // cout << st_num.size();
        string ret;
        for (auto e : st_str) {
            ret += e;
        }
        ret += tmp;
        return ret;
    }
};
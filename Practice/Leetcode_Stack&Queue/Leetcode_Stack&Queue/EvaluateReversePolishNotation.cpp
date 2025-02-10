#include "Stack&Queue.h"

// MySolution

class Solution {
public:
    // int StringToNumer(string stringNum){
    //     int ret = 0;
    //     int flag = 0;
    //     for(auto c : stringNum){
    //         if(c == '-'){
    //             flag = 1;
    //             continue;
    //         }
    //         ret *=10;
    //         ret += c - '0';

    //     }
    //     if(flag == 1) return 0-ret;
    //     return ret;
    // }

    int evalRPN(vector<string>& tokens) {
        stack<int> s;
        for (auto token : tokens) {
            if (token == "+") {
                int right = s.top();
                s.pop();
                int left = s.top();
                s.pop();
                s.push(left + right);
            }
            else if (token == "-") {
                int right = s.top();
                s.pop();
                int left = s.top();
                s.pop();
                s.push(left - right);
            }
            else if (token == "*") {
                int right = s.top();
                s.pop();
                int left = s.top();
                s.pop();
                s.push(left * right);
            }
            else if (token == "/") {
                int right = s.top();
                s.pop();
                int left = s.top();
                s.pop();
                s.push(left / right);
            }
            else {
                // int num = StringToNumer(token);
                int num = atoi(token.c_str());
                s.push(num);
            }
        }
        return s.top();
    }
};
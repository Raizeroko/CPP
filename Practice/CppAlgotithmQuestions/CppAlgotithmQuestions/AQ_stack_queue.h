#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<stack>

using namespace std;

class AQ_stack_queue {
public:
    int StringToNum(string token)
    {
        int ret = 0;
        int flag = 0;
        for (int i = 0; i < token.size(); i++)
        {
            if (token[i] == '-')
            {
                flag = 1;
                continue;
            }
            ret = ret * 10 + (token[i] - '0');
        }
        if (flag == 1)
            return (0 - ret);
        return ret;
    }

    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for (auto token : tokens)
        {
            if (token[token.size() - 1] >= '0' && token[token.size() - 1] <= '9')
            {
                int num = StringToNum(token);
                st.push(num);
            }
            else
            {
                int num1 = st.top();
                st.pop();
                int num2 = st.top();
                st.pop();
                if (token[0] == '+')
                {
                    st.push(num2 + num1);
                }
                if (token[0] == '-')
                {
                    st.push(num2 - num1);
                }
                if (token[0] == '*')
                {
                    st.push(num2 * num1);
                }
                if (token[0] == '/')
                {
                    st.push(num2 / num1);
                }
            }
        }
        return st.top();
    }
    //------------------------------------------------------------------//
    bool IsPopOrder(vector<int>& pushV, vector<int>& popV)
    {
    }

};
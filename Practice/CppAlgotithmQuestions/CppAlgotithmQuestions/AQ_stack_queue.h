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
    bool IsPopOrder(vector<int>& pushV, vector<int>& popV) {
        stack<int> st;
        int i = 0;
        int j = 0;
        while (i < pushV.size())
        {
            if (!st.empty() && st.top() == popV[j])
            {
                st.pop();
                j++;
                continue;
            }
            st.push(pushV[i++]);
        }
        while (j < popV.size())
        {
            int tmp = st.top();
            if (tmp != popV[j])
            {
                return false;
            }
            j++;
            st.pop();
        }
        return true;
    }
    //------------------------------------------------------------------//
    class MinStack {
    public:
        MinStack() {
        }

        void push(int val) {
            data.push(val);
            if (min.empty() || val < min.top())
            {
                min.push(val);
            }
            else
            {
                min.push(min.top());
            }
        }

        void pop() {
            data.pop();
            min.pop();
        }

        int top() {
            return data.top();
        }

        int getMin() {
            return min.top();
        }
        stack<int> data;
        stack<int> min;
    };
};
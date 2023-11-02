#define _CRT_SECURE_NO_WARNINGS 1

//Fibonacci数列
#include<iostream>
using namespace::std;
int main()
{
    int fib_pp = 0;
    int fib_p = 1;
    int fib = 0;
    int input = 0;
    cin >> input;
    if (input <= 3)
    {
        cout << 0;
        return 0;
    }
    while (fib < input)
    {
        fib = fib_pp + fib_p;
        fib_pp = fib_p;
        fib_p = fib;
        //cout << fib <<' '<< fib_pp<<"\n";
    }
    int ret = input - fib_pp < fib - input ? input - fib_pp : fib - input;
    cout << ret;
    return 0;
}


//合法序列括号判断
class Parenthesis {
public:
    bool chkParenthesis(string A, int n) {
        // write code here
        stack<char> tmp;
        for (int i = 0; i < A.size(); i++)
        {
            if (A[i] == '(')
            {
                tmp.push(A[i]);
            }
            else if (A[i] == ')')
            {
                if (tmp.empty())
                {
                    return false;
                }
                else
                {
                    tmp.pop();
                }
            }
            else
            {
                return false;
            }
        }
        if (tmp.empty())
        {
            return true;
        }
        return false;

    }
};
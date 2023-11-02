#define _CRT_SECURE_NO_WARNINGS 1

//两种排序方法
#include<iostream>
#include<string>
#include<vector>

using namespace::std;

int Is_Lex(const vector<string>& vstr)
{
    for (int i = 0; i < vstr.size() - 1; i++)
    {
        if (vstr[i] > vstr[i + 1])
        {
            return 0; //00
        }
    }
    return 2; //10
}
int Is_Len(const vector<string>& vstr)
{
    for (int i = 0; i < vstr.size() - 1; i++)
    {
        if (vstr[i].size() > vstr[i + 1].size())
        {
            return 0; //00
        }
    }
    return 1; //01
}
int main()
{
    int n;
    cin >> n;
    vector<string> tmp(n);
    for (auto& e : tmp)
    {
        cin >> e;
    }
    int flag = Is_Lex(tmp) | Is_Len(tmp);
    if (flag == 3)
    {
        cout << "both";
    }
    else if (flag == 2)
    {
        cout << "lexicographically";
    }
    else if (flag == 1)
    {
        cout << "lengths";
    }
    else
    {
        cout << "none";
    }
    return 0;
}


//求最小公倍数
#include<iostream>
using namespace::std;

int find_GCD(int a, int b)
{
    int tmp;
    if (a < b)
    {
        swap(a, b);
    }
    while (b != 0)
    {
        tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}
int main()
{
    int A, B;
    cin >> A >> B;
    int tmp = 0;
    tmp = find_GCD(A, B);
    cout << A * B / tmp;
    return 0;
}

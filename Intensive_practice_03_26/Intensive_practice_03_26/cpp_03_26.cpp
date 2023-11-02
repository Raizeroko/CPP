#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>

using namespace::std;

//不要二
int main()
{
    int w, h;
    cin >> w >> h;
    vector<vector<int>> tmp(w, vector<int>(h, 0));
    int ret = 0;
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            if (tmp[i][j] == 0)
            {
                ret++;
                if (i + 2 < w)
                {
                    tmp[i + 2][j] = 1;
                }
                if (j + 2 < h)
                {
                    tmp[i][j + 2] = 1;
                }
            }
        }
    }
    cout << ret;
    return 0;
}


//把字符串转换成数组
class Solution {
public:
    int StrToInt(string str) {
        int ret = 0;
        int flag = 0;
        if (str[0] == '-' || str[0] == '+')
        {
            flag = 1;
        }
        reverse(str.begin(), str.end());
        //cout <<str;
        for (int i = 0; i < str.size() - flag; i++)
        {
            if (str[i] >= '0' && str[i] <= '9')
            {
                ret += (str[i] - '0') * pow(10, i);
            }
            else
            {
                return 0;
            }
        }
        if (flag == 1 && str[str.size() - 1] == '-')
        {
            return 0 - ret;
        }
        return ret;
    }
};
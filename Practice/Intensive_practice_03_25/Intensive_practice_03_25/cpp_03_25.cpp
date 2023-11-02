#define _CRT_SECURE_NO_WARNINGS 1

//Day5
//BM72 连续子数组的最大和
class Solution {
public:
    int FindGreatestSumOfSubArray(vector<int> array) {
        vector<int> max(array.size(), 0);
        max[0] = array[0];
        for (int i = 1; i < array.size(); i++)
        {
            max[i] = array[i] > (max[i - 1] + array[i]) ? array[i] : max[i - 1] + array[i];
            //cout << max[i] << " ";
        }
        int ret = max[0];
        for (int i = 1; i < max.size(); i++)
        {
            if (max[i] > ret)
                ret = max[i];
        }
        return ret;
    }
};


//统计回文
#include<iostream>
#include<string>
using namespace std;
bool Is_Palindrome(string str1)   //判断回文
{
    int length = str1.length();
    for (int i = 0; i < length; i++)
    {
        if (str1[i] != str1[length - 1])
            return false;
        length = length - 1;
    }
    return true;
}
int main()
{
    string str1, str2, temp;
    int count, len;
    while (cin >> str1 >> str2)
    {
        count = 0;
        temp = str1;
        len = str1.length() + 1;
        for (int i = 0; i < len; i++)
        {
            str1 = temp;
            str1.insert(i, str2);   //在A字符串中以此插入B字符串
            if (Is_Palindrome(str1))       //判断是否是回文
                count = count + 1;    //统计回文    
        }
        cout << count << endl;
    }
    return 0;
}
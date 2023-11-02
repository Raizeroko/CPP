#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;


//面试题 01.01. 判定字符是否唯一
class Solution {
public:
    bool isUnique(string astr) {
        int tmp[26] = { 0 };
        for (auto e : astr)
        {
            tmp[e - 'a']++;
        }
        for (auto e : astr)
        {
            if (tmp[e - 'a'] != 1)
                return false;
        }
        return true;
    }
};

//面试题 01.02. 判定是否互为字符重排
class Solution {
public:
    bool CheckPermutation(string s1, string s2) {
        char tmp1[26] = { 0 };
        char tmp2[26] = { 0 };
        for (auto e : s1)
        {
            tmp1[e - 'a']++;
        }
        for (auto e : s2)
        {
            tmp2[e - 'a']++;
        }
        for (int i = 0; i < 26; i++)
        {
            if (tmp1[i] != tmp2[i])
                return false;
        }
        return true;
    }
};

//面试题 01.04. 回文排列
class Solution {
public:
    bool canPermutePalindrome(string s) {
        int tmp[128] = { 0 };
        for (auto e : s)
        {
            tmp[e]++;
        }
        int flag = 0;
        for (int i = 0; i < 128; i++)
        {
            if (tmp[i] % 2 == 1)
                flag++;
        }
        if (flag < 2)
            return true;
        else
            return false;
    }
};

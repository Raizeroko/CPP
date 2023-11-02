#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<vector>

using namespace::std;

//JZ42 连续子数组的最大和
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

//136. 只出现一次的数字
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ret = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            ret ^= nums[i];
        }
        return ret;
    }
};

//17. 电话号码的字母组合
class Solution {
    string num_word[10] = { "", "", "abc", "def", "ghi","jkl", "mno", "pqrs", "tuv", "wxyz" };
public:
    void _letterCombinations(string& digits, vector<string>& ret, string tmp, size_t i)
    {
        if (i == digits.size())
        {
            ret.push_back(tmp);
            return;
        }
        string word = num_word[digits[i] - '0'];
        for (size_t j = 0; j < word.size(); j++)
        {
            _letterCombinations(digits, ret, tmp + word[j], i + 1);
        }

    }
    vector<string> letterCombinations(string digits) {
        vector<string> ret;
        string tmp;
        if (digits.empty())
        {
            return ret;
        }
        _letterCombinations(digits, ret, tmp, 0);
        return ret;
    }
};

//

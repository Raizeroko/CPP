#pragma once
#include<iostream>
#include<string>
#include<vector>

using namespace std;

class AQ_vector {
public:
    vector<string> mapping = { "","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz" };

    void conbine(vector<string>& ret, string& digits, string reti, size_t pos)
    {
        if (pos == digits.size())
        {
            ret.push_back(reti);
            return;
        }
        string map = mapping[digits[pos] - '0'];
        for (int i = 0; i < map.size(); i++)
        {
            string tmp = reti;
            tmp += map[i];
            conbine(ret, digits, tmp, pos + 1);
        }
    }

    vector<string> letterCombinations(string digits) 
    {
        vector<string> ret;
        string tmp;
        if (digits.empty())
        {
            return ret;
        }
        conbine(ret, digits, tmp, 0);
        return ret;
    }
    //------------------------------------------------------------------//
    vector<int> singleNumber(vector<int>& nums) 
    {
        int sum = 0;
        for (auto e : nums)
        {
            sum ^= e;
        }
        int i = 1;
        //�ҵ�sum�Ķ�������ʽ�е�һλΪ1�ĵ�λ��
        //sum���ܲ������������ᵼ�·������˳�
        // for (; i <= sum; i = i << 1)
        // {
        //     if ((sum & i) != 0)
        //     {
        //         break;
        //     }
        // }

        while ((sum & i) == 0) {
            i = i << 1;
        }
        int sum1 = 0;
        int sum2 = 0;
        for (auto e : nums)
        {
            if ((e & i) == i)
            {
                sum1 ^= e;
            }
            else
            {
                sum2 ^= e;
            }
        }

        vector<int> ret;
        ret.push_back(sum1);
        ret.push_back(sum2);
        return ret;
    }
};
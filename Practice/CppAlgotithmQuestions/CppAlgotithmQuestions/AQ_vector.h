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
    vector<int> singleNumber2to2(vector<int>& nums) 
    {
        int sum = 0;
        for (auto e : nums)
        {
            sum ^= e;
        }
        int i = 1;
        //找到sum的二进制形式中第一位为1的的位置
        //sum可能不是正数这样会导致非正常退出
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
    //------------------------------------------------------------------//
    int singleNumber3to1(vector<int>& nums) 
    {
        int ret = 0;
        for (int i = 0; i < 32; i++)
        {
            int sum = 0;
            for (auto e : nums)
            {
                sum += ((e >> i) & 1);
            }
            if (sum % 3)
            {
                ret |= (1 << i);
            }
        }
        return ret;
    }
    //------------------------------------------------------------------//
    vector<vector<int>> generate(int numRows) 
    {
        vector<vector<int>> ret;
        for (int i = 1; i <= numRows; i++)
        {
            vector<int> v(i, 1);
            ret.push_back(v);
        }
        for (int i = 2; i < ret.size(); i++)
        {
            //除去每行第一个和最后一个元素
            for (int j = 1; j < ret[i].size() - 1; j++)
            {
                ret[i][j] = ret[i - 1][j - 1] + ret[i - 1][j];
            }
        }
        return ret;
    }
    //------------------------------------------------------------------//
    int removeDuplicates(vector<int>& nums) 
    {
        int first = 0;
        int last = 0;
        while (last < nums.size())
        {
            if (nums[first] == nums[last])
            {
                last++;
            }
            else
            {
                first++;
                nums[first] = nums[last];
            }
        }
        return first + 1;
    }
    //------------------------------------------------------------------//
    void test()
    {
        int ar[] = { 1,2,3,4,0,5,6,7,8,9 };
        int n = sizeof(ar) / sizeof(int);
        vector<int> v(ar, ar + n);
        vector<int>::iterator it = v.begin();
        while (it != v.end())

        {

            if (*it != 0)

                cout << *it;

            else

                v.erase(it);

            it++;

        }
    }
    //------------------------------------------------------------------//
    int FindGreatestSumOfSubArray(vector<int>& array) 
    {
        // write code here
        vector<int> ret(array.size());
        ret[ret.size() - 1] = array[array.size() - 1];
        for (int i = array.size() - 2; i >= 0; i--)
        {
            if (array[i] > array[i] + ret[i + 1])
            {
                ret[i] = array[i];
            }
            else
            {
                ret[i] = array[i] + ret[i + 1];
            }
        }
        int max = ret[0];
        for (int tmp : ret)
        {
            max = max > tmp ? max : tmp;
        }
        return max;
    }
    //------------------------------------------------------------------//
    int MoreThanHalfNum_Solution(vector<int>& numbers) {
        // write code here
        int ret = -1;
        int count = 0;
        for (auto num : numbers)
        {
            if (ret == num || count == 0)
            {
                ret = num;
                count++;
            }
            if (ret != num)
            {
                count--;
            }
        }
        return ret;
    }
    //------------------------------------------------------------------//
    int singleNumber2to1(vector<int>& nums) {
        int ret = 0;
        for (int num : nums)
        {
            ret ^= num;
        }
        return ret;
    }
    //------------------------------------------------------------------//
};
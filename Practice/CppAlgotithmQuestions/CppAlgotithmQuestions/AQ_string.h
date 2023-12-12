#pragma once
#include<iostream>
#include<string>
#include<vector>

using namespace std;

class AQ_string {
public:
	void OnlyOne()
	{
        string s;
        vector<int> v;
        v.reserve(26);
        cin >> s;
        for (auto ch : s)
        {
            v[ch - 'a']++;
        }
        for (auto ch : s)
        {
            if (v[ch - 'a'] == 1)
            {
                cout << ch;
                return ;
            }
        }
        cout << -1;
	}
    //------------------------------------------------------------------//
    void reverse(string& s, int i, int j)
    {
        while (i < j)
        {
            swap(s[i], s[j]);
            i++;
            j--;
        }
    }
    string reverseWords(string s) {
        int first = 0;
        int last = 0;
        while (first < s.size())
        {
            while (last != s.size() && s[last] != ' ')
            {
                last++;
            }
            reverse(s, first, last - 1);
            last++;
            first = last;
        }
        return s;
    }
    //------------------------------------------------------------------//
    string reverseStr(string s, int k) {
        int first = 0;
        int last = 0;
        while (first < s.size())
        {
            while (last != s.size() && last - first < 2 * k)
            {
                last++;
            }
            if (first + k > s.size())
                reverse(s, first, s.size() - 1);
            else
                reverse(s, first, first + k - 1);
            first = last;
        }
        return s;
    }
    //------------------------------------------------------------------//
    bool Palindrome(string s)
    {
        int first = 0;
        int last = s.size() - 1;
        while (first < last)
        {
            if (s[first++] != s[last--])
                return false;
        }
        return true;
    }
    bool isPalindrome(string s) {
        int i = 0;
        while (i < s.size())
        {
            if (s[i] >= 'A' && s[i] <= 'Z')
            {
                s[i] = tolower(s[i]);
            }
            else if ((s[i] < 'a' || s[i] > 'z') && (s[i] < '0' || s[i] > '9'))
            {
                s.erase(i, 1);
                continue;
            }
            i++;

        }
        return Palindrome(s);
    }
    //------------------------------------------------------------------//
    void FindLastWord()
    {
        string str;
        getline(cin, str);
        int last = str.find_last_of(' ');
        cout << str.size() - last - 1;
    }
    //------------------------------------------------------------------//
    int firstUniqChar(string s) {
        vector<int> tmp(26, 0);
        for (int i = 0; i < s.size(); i++)
        {
            tmp[s[i] - 'a']++;
        }
        for (int i = 0; i < s.size(); i++)
        {
            if (tmp[s[i] - 'a'] == 1)
                return i;
        }
        return -1;
    }
    //------------------------------------------------------------------//
    void reverseString(vector<char>& s) {
        int first = 0;
        int last = s.size() - 1;
        while (first < last)
        {
            swap(s[first++], s[last--]);
        }
    }
    //------------------------------------------------------------------//
    void reverse(string& s)
    {
        int i = 0;
        int j = s.size() - 1;
        while (i < j)
        {
            swap(s[i], s[j]);
            i++;
            j--;
        }
    }
    string addStrings(string num1, string num2) {
        string ret;
        int carry = 0;
        int i = num1.size() - 1;
        int j = num2.size() - 1;
        for (; i >= 0 && j >= 0; i--, j--)
        {
            int sum = num1[i] + num2[j] + carry - 2 * '0';
            if (sum > 9)
            {
                carry = 1;
                sum -= 10;
            }
            else
            {
                carry = 0;
            }
            ret += sum + '0';
        }
        while (i >= 0)
        {
            int sum = num1[i--] + carry - '0';
            if (sum > 9)
            {
                ret += '0';
                carry = 1;
            }
            else
            {
                ret += sum + '0';
                carry = 0;
            }
        }
        while (j >= 0)
        {
            int sum = num2[j--] + carry - '0';
            if (sum > 9)
            {
                ret += '0';
                carry = 1;
            }
            else
            {
                ret += sum + '0';
                carry = 0;
            }
        }
        if (carry == 1)
        {
            ret += '1';
        }
        reverse(ret);
        return ret;
    }
    //------------------------------------------------------------------//
    bool isAvailable(char ch)
    {
        if (ch == '+' || ch == '-')
            return true;
        else if (ch < '0' || ch > '9')
            return false;
        return true;
    }
    int StrToInt(string str) {
        int ret = 0;
        int flag = 0;
        for (auto ch : str)
        {
            if (!isAvailable(ch))
            {
                return 0;
            }
            if (ch == '+')
            {
                flag = 0;
                continue;
            }
            else if (ch == '-')
            {
                flag = 1;
                continue;
            }
            ret = ret * 10 + ch - '0';
        }
        if (flag == 1)
            return 0 - ret;
        return ret;
    }
    // 
    string mul(string num1, char ch)
    {
        string ret;
        int carry = 0;
        int mul = 0;
        for (int i = num1.size() - 1; i >= 0; i--)
        {
            mul = (num1[i] - '0') * (ch - '0') + carry;
            carry = mul / 10;
            mul = mul % 10;
            ret += mul + '0';
        }
        if (carry)
        {
            ret += carry + '0';
        }
        return ret;
    }
    string multiply(string num1, string num2) {
        string ret;
        for (int i = num2.size() - 1; i >= 0; i--)
        {
            //²¹0
            int zero = num2.size() - i - 1;
            string tmp;
            while (zero)
            {
                tmp += '0';
                zero--;
            }
            tmp += mul(num1, num2[i]);
            reverse(tmp);
            //×Ö·û´®Ïà¼Ó£ºret+=tmp;
            ret = addStrings(ret, tmp);
        }
         while(ret[0] == '0' && ret.size() > 1)
             ret.erase(0,1);
        return ret;
    }

};
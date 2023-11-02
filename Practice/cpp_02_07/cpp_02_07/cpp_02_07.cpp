#define _CRT_SECURE_NO_WARNINGS 1

//1859. 将句子排序

#include <iostream>
#include <string>

using namespace std;


class Solution {
public:
    string sortSentence(string s) {
        //s为空
        if (s.size() == 0)
            return s;

        //s不为空
        string ret;
        char find = '1';
        size_t tail = s.find(find);

        while (tail != string::npos)
        {
            cout << tail << endl;
            //找到头尾
            size_t head;
            head = s.rfind(' ', tail);

            if (head == string::npos)  //说明是第一个单词
            {
                head = 0;
            }
            else              //不是第一个单词，找到了空格，++head得到所找单词的第一个字母
            {
                head++;
            }
            ret.append(s, head, tail - head);
            ret += ' ';
            find++;
            tail = s.find(find);
        }

        ret.pop_back();
        return ret;
    }
};

int main()
{
    string a = "is2 sentence4 This1 a3";
    

    cout << sortSentence(a) << endl;

    return 0;
}
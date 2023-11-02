#define _CRT_SECURE_NO_WARNINGS 1

//class BinInsert {
//public:
//    int binInsert(int n, int m, int j, int i) {
//        // write code here
//        n |= (m << j);
//        return n;
//
//    }
//};

#include<iostream>

using namespace::std;

bool Is_primenumber(int tmp)
{
    if (tmp <= 3)
    {
        return true;
    }
    int i = tmp - 1;
    while (i > 1)
    {
        if (tmp % i == 0)
        {
            return false;
        }
        i--;
    }
    return true;
}

int main()
{
    int input;
    cin >> input;

    int big = input / 2;
    int small = big;
    do
    {
        if (big + small < input)
        {
            big++;
        }
        if (big + small > input)
        {
            small--;
        }
        while (!Is_primenumber(big))
        {
            big++;
        }
        while (!Is_primenumber(small))
        {
            small--;
        }

    } while (small + big != input);

    cout << small << "\n" << big;
}
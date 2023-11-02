#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<string>

using namespace::std;

//Day 3
// 
//int main()
//{
//    string input;
//    cin >> input;
//    string output = "";
//    int slow = 0;
//    int fast = 0;
//    //int max = 0;
//
//    while (fast < input.size())
//    {
//        if (input[fast] >= '0' && input[fast] <= '9')
//        {
//            fast++;
//        }
//        else if (fast != slow)
//        {
//            if (fast - slow > output.size())
//            {
//                output = "";
//                output.append(input, slow, fast - slow);
//                slow = fast;
//                cout<<output;
//            }
//        }
//        else
//        {
//            slow++;
//            fast++;
//        }
//    }
//    if (fast != slow && fast - slow > output.size())
//    {
//        output = "";
//        output.append(input, slow, fast - slow);
//    }
//    cout << output;
//    return 0;
//}

//
int main()
{
    int m = 0123, n = 123;
    printf("%o,%o", m, n);
    return 0;
}



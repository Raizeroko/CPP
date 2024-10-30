#pragma once
#include <iostream>
using namespace std;

class ListNode {
    ListNode(int data)
        :val(data)
        , next(nullptr)
    {}

public:
    int val;
    ListNode* next;
};

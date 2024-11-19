#pragma once
#include <iostream>
#include <stack>
using namespace std;

class ListNode {
public:
    ListNode()
        :val(0)
        ,next(nullptr)
    {}
    ListNode(int data)
        :val(data)
        , next(nullptr)
    {}

public:
    int val;
    ListNode* next;
};

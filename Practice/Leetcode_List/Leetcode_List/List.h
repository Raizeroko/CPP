#pragma once
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
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
    ListNode(int x, ListNode* next) 
        : val(x)
        , next(next) 
    {}

public:
    int val;
    ListNode* next;
};

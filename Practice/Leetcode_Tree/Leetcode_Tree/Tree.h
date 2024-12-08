#pragma once
#include <math.h>
#include <algorithm>
#include <iostream>
using namespace std;

class TreeNode{
	TreeNode()
		: val(0)
		, left(nullptr)
		, right(nullptr)
	{}
	TreeNode(int x) 
		: val(x)
		, left(nullptr)
		, right(nullptr) 
	{}
	TreeNode(int x, TreeNode* left, TreeNode* right) 
		: val(x)
		, left(left)
		, right(right) 
	{}

public:
	int val;
	TreeNode* left;
	TreeNode* right;
};
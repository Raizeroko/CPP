#pragma once
#include <math.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class TreeNode{
public:
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


// ��������������
TreeNode* constructTree(const std::vector<int>& values) {
    if (values.empty()) return nullptr;

    TreeNode* root = new TreeNode(values[0]);
    std::queue<TreeNode*> q;
    q.push(root);
    size_t i = 1;

    while (i < values.size()) {
        TreeNode* current = q.front();
        q.pop();

        // ����������
        if (i < values.size() && values[i] != -1) { // ����-1��ʾ�սڵ�
            current->left = new TreeNode(values[i]);
            q.push(current->left);
        }
        i++;

        // ����������
        if (i < values.size() && values[i] != -1) {
            current->right = new TreeNode(values[i]);
            q.push(current->right);
        }
        i++;
    }

    return root;
}

// ��ӡ���ļ�ʾ��
void printTree(TreeNode* root) {
    if (!root) return;
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        if (current) {
            std::cout << current->val << " ";
            q.push(current->left);
            q.push(current->right);
        }
        else {
            std::cout << "null ";
        }
    }
    std::cout << std::endl;
}


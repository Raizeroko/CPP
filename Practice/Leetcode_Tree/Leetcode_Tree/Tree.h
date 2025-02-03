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


// 构建二叉树函数
TreeNode* constructTree(const std::vector<int>& values) {
    if (values.empty()) return nullptr;

    TreeNode* root = new TreeNode(values[0]);
    std::queue<TreeNode*> q;
    q.push(root);
    size_t i = 1;

    while (i < values.size()) {
        TreeNode* current = q.front();
        q.pop();

        // 构造左子树
        if (i < values.size() && values[i] != -1) { // 假设-1表示空节点
            current->left = new TreeNode(values[i]);
            q.push(current->left);
        }
        i++;

        // 构造右子树
        if (i < values.size() && values[i] != -1) {
            current->right = new TreeNode(values[i]);
            q.push(current->right);
        }
        i++;
    }

    return root;
}

// 打印树的简单示例
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


#include "FixedLengthMemoryPool.h"
#include "Utils.h"

#include <iostream>
#include <vector>

// TestCode
void testAlignSize() {
	// Utils utils;

	// 测试 AlignSize 方法
	assert(Utils::AlignSize(10) == 16); // 8 byte对齐
	assert(Utils::AlignSize(128) == 128); // 16 byte对齐
	assert(Utils::AlignSize(150) == 160); // 16 byte对齐
	assert(Utils::AlignSize(1025) == 1152); // 128 byte对齐
	assert(Utils::AlignSize(2000) == 2048); // 1024 byte对齐
	assert(Utils::AlignSize(100000) == 106496); // 8*1024 byte对齐

	std::cout << "AlignSize test passed!" << std::endl;
}

void testIndex() {
	//Utils utils;

	// 测试 Index 方法
	assert(Utils::Index(10) == 1); // 在第一个区间
	assert(Utils::Index(100) == 12); // 在第一个区间
	assert(Utils::Index(500) == 47); // 在第二个区间
	assert(Utils::Index(1500) == 83); // 在第三个区间
	assert(Utils::Index(50000) == 176); // 在第四个区间
	assert(Utils::Index(150000) == 202); // 在第五个区间

	std::cout << "Index test passed!" << std::endl;
}



// Text Code
using std::vector;
using std::cout;
using std::cin;
using std::endl;

struct TreeNode {
	int _val; TreeNode* _left; TreeNode* _right;
	TreeNode()
		:_val(0)
		, _left(nullptr)
		, _right(nullptr) {}
};

void testFixedLengthMemoryPool() {
	// 申请释放的轮次
	const size_t Rounds = 3;
	// 每轮申请释放多少次
	const size_t N = 100000;
	size_t begin1 = clock();
	std::vector<TreeNode*> v1; v1.reserve(N);
	for (size_t j = 0; j < Rounds; ++j) {
		for (int i = 0; i < N; ++i) {
			v1.push_back(new TreeNode);
		}
		for (int i = 0; i < N; ++i) {
			delete v1[i];
		} v1.clear();
	}
	size_t end1 = clock();
	FixedLengthMemoryPool<TreeNode> TNPool;
	size_t begin2 = clock();
	std::vector<TreeNode*> v2;
	v2.reserve(N);
	for (size_t j = 0; j < Rounds; ++j)
	{
		for (int i = 0; i < N; ++i) {
			v2.push_back(TNPool.New());
		}
		for (int i = 0; i < N; ++i) {
			TNPool.Delete(v2[i]);
		}
		v2.clear();
	}
	size_t end2 = clock();
	cout << "new cost time:" << end1 - begin1 << endl;
	cout << "object pool cost time:" << end2 - begin2 << endl;
}



int main() {
	//testFixedLengthMemoryPool();
	testAlignSize();
	testIndex();
}



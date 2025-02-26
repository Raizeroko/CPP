#include "FixedLengthMemoryPool.h"
#include "HarshMapRules.h"

#include <iostream>
#include <vector>

// TestCode
void testAlignSize() {
	HarshMap harshMap;

	// ���� AlignSize ����
	assert(harshMap.AlignSize(10) == 16); // 8 byte����
	assert(harshMap.AlignSize(128) == 128); // 16 byte����
	assert(harshMap.AlignSize(150) == 160); // 16 byte����
	assert(harshMap.AlignSize(1025) == 1152); // 128 byte����
	assert(harshMap.AlignSize(2000) == 2048); // 1024 byte����
	assert(harshMap.AlignSize(100000) == 106496); // 8*1024 byte����

	std::cout << "AlignSize test passed!" << std::endl;
}

void testIndex() {
	HarshMap harshMap;

	// ���� Index ����
	assert(harshMap.Index(10) == 1); // �ڵ�һ������
	assert(harshMap.Index(100) == 12); // �ڵ�һ������
	assert(harshMap.Index(500) == 47); // �ڵڶ�������
	assert(harshMap.Index(1500) == 83); // �ڵ���������
	assert(harshMap.Index(50000) == 176); // �ڵ��ĸ�����
	assert(harshMap.Index(150000) == 202); // �ڵ��������

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
	// �����ͷŵ��ִ�
	const size_t Rounds = 3;
	// ÿ�������ͷŶ��ٴ�
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



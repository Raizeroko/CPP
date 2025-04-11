#include <vector>
#include <queue>
#include <iostream>
#include <functional>
using namespace std;

class Heap {
public:
	Heap(const vector<int> nums) {
		for (auto num : nums) {
			_heap.push_back(num);
			AdjustUp();
		}
	}
	bool empty() {
		return _heap.empty();
	}

	int top() {
		if (!empty()) {
			return _heap[0];
		}
	}

	void pop() {
		swap(_heap.front(), _heap.back());
		_heap.resize(_heap.size() - 1);
		AdjustDown();
	}

	void AdjustUp() {
		int cur = _heap.size() - 1;
		while (cur > 0) {
			int parent = (cur - 1) / 2;
			if (_heap[cur] > _heap[parent]) {
				swap(_heap[cur], _heap[parent]);
				cur = parent;
			}
			else {
				break;
			}
		}
	}
	void AdjustDown() {
		int cur = 0;
		while (cur < _heap.size()) {
			int child = cur * 2 + 1;
			if (child + 1 < _heap.size() && _heap[child] < _heap[child + 1]) {
				child++;
			}
			if (child >= _heap.size()) return;

			if (_heap[cur] < _heap[child]) {
				swap(_heap[cur], _heap[child]);
				cur = child;
			}
			else {
				return;
			}
		}
	}

	void print() {
		for (auto num : _heap) {
			cout << num << " ";
		}
	}

private:
	vector<int> _heap;
};


void HeapSort(vector<int>& nums) {
	Heap h(nums);
	for (int i = 0; i < nums.size(); i++) {
		nums[i] = h.top();
		h.pop();
	}
}

int main() {
	vector<int> nums = { 3, 6, 8, 2, 9, 1, 8, 4, 3, 7 };
	HeapSort(nums);
	for (auto num : nums) {
		cout << num << endl;
	}
	return 0;
}
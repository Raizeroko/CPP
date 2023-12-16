#include "PriorityQueue.h"
#include<deque>

using namespace zwr;

int main()
{
	//test:priority_queue<int, vector<int>, less<int>>
	priority_queue<int> vector_less_pq;
	vector_less_pq.push(0);
	vector_less_pq.push(5);
	vector_less_pq.push(2);
	vector_less_pq.push(4);
	vector_less_pq.push(3);
	vector_less_pq.push(1);
	while (!vector_less_pq.empty())
	{
		cout << vector_less_pq.top() << ' ';
		vector_less_pq.pop();
	}
	cout << endl;
	//test:priority_queue<int,deque<int>, Less<int>>
	priority_queue<int, deque<int>> deque_less_pq;
	deque_less_pq.push(0);
	deque_less_pq.push(5);
	deque_less_pq.push(2);
	deque_less_pq.push(4);
	deque_less_pq.push(3);
	deque_less_pq.push(1);
	while (!deque_less_pq.empty())
	{
		cout << deque_less_pq.top() << ' ';
		deque_less_pq.pop();
	}
	cout << endl;
	//test:priority_queue<int, vector<int>, Greater<int>>
	priority_queue<int, vector<int>, Greater<int>> vector_greater_pq;
	vector_greater_pq.push(0);
	vector_greater_pq.push(5);
	vector_greater_pq.push(2);
	vector_greater_pq.push(4);
	vector_greater_pq.push(3);
	vector_greater_pq.push(1);
	while (!vector_greater_pq.empty())
	{
		cout << vector_greater_pq.top() << ' ';
		vector_greater_pq.pop();
	}
	cout << endl;
	//priority_queue<int, deque<int>, Greater<int>>
	priority_queue<int, deque<int>, Greater<int>> deque_greater_pq;
	deque_greater_pq.push(0);
	deque_greater_pq.push(5);
	deque_greater_pq.push(2);
	deque_greater_pq.push(4);
	deque_greater_pq.push(3);
	deque_greater_pq.push(1);
	while (!deque_greater_pq.empty())
	{
		cout << deque_greater_pq.top() << ' ';
		deque_greater_pq.pop();
	}
	cout << endl;
	return 0;
}
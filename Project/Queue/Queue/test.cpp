#include<iostream>
#include<vector>
#include<deque>
#include"Queue.h"

using namespace std;
using namespace zwr;

void test_list_queue()
{
	queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);

	cout << q.size() << endl;

	while (!q.empty())
	{
		cout << "front:" << q.front() << "     back:" << q.back() << endl;
		q.pop();
	}
	cout << endl;
}

void test_deque_queue()
{
	queue<int, deque<int>> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);

	cout << q.size() << endl;

	while (!q.empty())
	{
		cout << "front:" << q.front() << "     back:" << q.back() << endl;
		q.pop();
	}
	cout << endl;
}

int main()
{
	test_list_queue();
	test_deque_queue();
	return 0;
}
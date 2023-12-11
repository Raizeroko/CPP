#include"Stack.h"
#include<vector>
#include<deque>

using namespace std;
using namespace zwr;

void test_deque_stack()
{
	stack<int, deque<int>> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	st.push(5);
	cout << st.size() << endl;
	while (!st.empty())
	{
		cout << st.top() << ' ';
		st.pop();
	}
	cout << endl;
}

void test_vector_stack()
{
	stack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	st.push(5);
	cout << st.size()<< endl;
	while (!st.empty())
	{
		cout << st.top()<< ' ';
		st.pop();
	}
	cout << endl;
}

int main()
{
	test_vector_stack();
	test_deque_stack();
	return 0;
}
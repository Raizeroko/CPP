#include <iostream>
#include <stack>
using namespace std;


//(9)-д������ Ack(m,n)�ĵݹ��㷨�������ݴ��㷨����Ack(2,1)�ļ������
//   -д������Ack(m, n)�ķǵݹ��㷨��
int Ackermann_recurrence(int m, int n)
{
	if (m == 0)
		return n + 1;
	else if (m != 0 && n == 0)
		return Ackermann_recurrence(m - 1, 1);
	else
		return Ackermann_recurrence(m - 1, Ackermann_recurrence(m, n - 1));
}


int Ackermann(int m, int n)
{
	stack<int> stack;
	stack.push(m);
	stack.push(n);
	int nn, mm;
	while (stack.size() != 1)
	{
		nn = stack.top();
		stack.pop();
		mm = stack.top();
		stack.pop();
		if (mm == 0)
		{
			nn += 1;
			stack.push(nn);
		}
		else if (mm != 0 && nn == 0)
		{
			stack.push(mm - 1);
			stack.push(1);
		}
		else
		{
			stack.push(mm - 1);
			stack.push(mm);
			stack.push(nn - 1);
		}
	}
	return nn;
}



int main()
{
	cout << Ackermann(2, 1);
	return 0;
}
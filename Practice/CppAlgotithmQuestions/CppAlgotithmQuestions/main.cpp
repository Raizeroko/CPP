#include<iostream>
#include"AQ_string.h"
#include"AQ_vector.h"
#include"AQ_stack_queue.h"

void test_AQ_string()
{
	AQ_string aq;
	aq.addStrings("11", "123");
	cout << aq.multiply("2", "3");
}


void test_AQ_vector()
{
	AQ_vector aq;
	vector<string> ret =aq.letterCombinations("23");
	for (auto e : ret)
	{
		cout << e << ' ';
	}
	cout << endl;
	vector<int> vec = { 1,2,1,3,2,5 };
	aq.singleNumber2to2(vec);
	//aq.test();
	vector<int> v = { 1,2,3,2,2,2,5,4,2 };
	aq.MoreThanHalfNum_Solution(v);

}

void test_AQ_stack_queue()
{
	AQ_stack_queue aq;
	vector<string> input={ "10","6","9","3","+","-11","*","/","*","17","+","5","+" };
	cout<<aq.evalRPN(input);
	vector<int> pushV = { 2,1,0 };
	vector<int> popV = { 1,2,0 };

	aq.IsPopOrder(pushV, popV);
}


int main()
{
	//test_AQ_string();
	//test_AQ_vector();
	test_AQ_stack_queue();
	
}
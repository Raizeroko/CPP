#include<iostream>
#include"AQ_string.h"
#include"AQ_vector.h"

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
	aq.singleNumber(vec);

}

int main()
{
	//test_AQ_string();
	test_AQ_vector();

	
}
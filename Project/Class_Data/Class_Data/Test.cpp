#include"Data.h"

void test3()
{
	Data d1;
	Data d2;
	cin >> d1 >> d2;
	cout << d1 << d2;
}

void test2()
{
	Data d1(2022, 1, 9);
	Data d2(2022, 1, 8);
	Data d3(2022, 1, 7);
	d1 = d1 + 1 + 1 + 1;
	d1.Print();
	d1 = d2 = d3;
	d1.Print();
}

void test1()
{
	Data d1(2022, 1, 9);
	d1.Print();
	Data d2(2022, 1, 8);
	Data d3(d1);

	d1 += 100;
	d1.Print();
	d1 -= 110;
	d1.Print();
	d1 = d1 + 110;
	d1.Print();
	d1 = d1 - 100;
	d1.Print();
	cout << d1 - d2 << endl;
	if (d1 > d2)
	{
		cout << "d1>d2" << endl;
	}
	if (d2 < d1)
	{
		cout << "d2<d1" << endl;
	}
	if (d2 != d1)
	{
		cout << "d1!=d2" << endl;
	}
	if (d1 == d3)
	{
		cout << "d1==d3" << endl;
	}
	if (d1 <= d3)
	{
		cout << "d1<=d3" << endl;
	}
	if (d1 >= d3)
	{
		cout << "d1>=d3" << endl;
	}
}

int main()
{
	//test1();
	//test2();
	test3();
	return 0;

}
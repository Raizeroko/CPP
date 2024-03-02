#include <iostream>
using namespace std;


class A {
public:

	A()
	{
		cout << "A" << endl;
	}
	void fun() {}
	~A()
	{
		cout << "~A" << endl;
	}
	int a;
};

class B : public A 
{
public:
	B()
	{
		cout << "B" << endl;
	}
	void fun() {}
	~B()
	{
		cout << "~B" << endl;
	}


public:
	int b;
};


int main() {
	B b;



}
#pragma once

#include<iostream>
#include<assert.h>

using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;

class Data {
	friend ostream& operator<<(ostream& out, const Data& d);
	friend istream& operator>>(istream& in, Data& d);
public:
	
	Data(int year = 0, int month = 1, int day = 0);
	void Print();
	int GetMonthDay(int year, int month);
	
	//operator
	Data operator+(int day);
	Data& operator+=(int day);
	Data operator-(int day);
	Data& operator-=(int day);
	Data operator++(int);
	Data& operator++();
	Data operator--(int);
	Data& operator--();
	int operator-(Data& d);
	bool operator>(Data& d);
	bool operator==(Data& d);
	bool operator<(Data& d);
	bool operator!=(Data& d);
	bool operator<=(Data& d);
	bool operator>=(Data& d);

	
	
private:
	int _year;
	int _month;
	int _day;

};


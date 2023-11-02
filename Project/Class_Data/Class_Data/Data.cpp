#include "Data.h"

//得到当月天数
int Data::GetMonthDay(int year, int month)
{
	int MonthDays[13] = {0, 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		return 29;
	return MonthDays[month];

}

//构造函数
Data::Data(int year, int month, int day)
{
	if (year < 0 || month < 1 || month >12 || day<0 || day> GetMonthDay(year, month))
	{
		cout << "非法日期" << endl;
	}
	_year = year;
	_month = month;
	_day = day;

}

//打印
void Data::Print()
{
	cout << _year << '-' << _month << '-' << _day << endl;
}

//operator
//operator A + day
Data Data::operator+(int day)
{
	Data ret(*this);
	ret += day;
	return ret;
}
//operator A += day
Data& Data::operator+=(int day)
{
	if (day < 0)
	{
		return *this -= -day;
	}
	_day += day;
	while (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year, _month);
		_month++;
		if (_month > 12)
		{
			_year++;
			_month = 1;
		}
	}
	return *this;
}
//operator A - day
Data Data::operator-(int day)
{
	Data ret(*this);
	ret -= day;
	return ret;
}
//operator A -= day
Data& Data::operator-=(int day)
{
	if (day < 0)
	{
		return *this += day;
	}

	_day -= day;
	while (_day < 1)
	{
		_month--;
		if (_month < 1)
		{
			_month = 12;
			_year--;
		}
		_day += GetMonthDay(_year, _month);
	}
	return *this;
}
//operator A++
Data Data::operator++(int)
{
	Data ret(*this);
	*this += 1;
	return ret;
}
//operator ++A
Data& Data::operator++()
{
	*this += 1;
	return *this;
}
//operator B++
Data Data::operator--(int)
{
	Data ret(*this);
	*this -= 1;
	return ret;
}
//operator ++B
Data& Data::operator--()
{
	*this -= 1;
	return *this;
}
//opertor A - B
int Data::operator-(Data& d)
{
	Data max = *this;
	Data min = d;
	int flag = 1;
	int n = 0;
	if (*this < d)
	{
		max = d;
		min = *this;
		flag = -1;
	}
	while (max > min)
	{
		min++;
		n++;
	}
	return n * flag;
}
//operator A > B
bool Data::operator>(Data& d)
{
	if (_year > d._year)
		return true;
	else if (_year == d._year && _month > d._month)
		return true;
	else if (_year == d._year && _month == d._month && _day > d._day)
		return true;
	return false;
}
//operator A == B
bool Data::operator==(Data& d)
{
	if (_year == d._year && _month == d._month && _day == d._day)
		return true;
	return false;
}
//operator A < B
bool Data::operator<(Data& d)
{
	return !(*this >= d);
}
//operator A != B
bool Data::operator!=(Data& d)
{
	return !(*this == d);
}
//operator A >= B
bool Data::operator>=(Data& d)
{
	return (*this > d) || (*this == d);
}
//operator A <= B
bool Data::operator<=(Data& d)
{
	return !(*this > d);
}

//cout<<d
ostream& operator<<(ostream& out, const Data& d)
{
	out << d._year << "-" << d._month << "-" << d._day << endl;
	return out;
}
//cin>>d
istream& operator>>(istream& in, Data& d)
{
	in >> d._year >> d._month >> d._day;
	return in;
}

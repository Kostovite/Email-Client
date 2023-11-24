#pragma once

#include <iostream>
#include <string>

class Date {
private:
	int _day;
	int _month;
	int _year;
public:
	Date();
	Date(int day, int month, int year);
	~Date();
public:
	int getDay();
	int getMonth();
	int getYear();
	void setDay(int day);
	void setMonth(int month);
	void setYear(int year);
	Date getToday();
public:
	//Operator +, -, ++, --, +=, -=
	Date operator + (int day);
	Date operator - (int day);
	Date operator + (Date date);
	Date operator - (Date date);
	Date operator ++ ();
	Date operator -- ();
	Date operator += (Date date);
	Date operator -= (Date date);
};
#include "../EmailUI/pch.h"
#include "Date.h"

#include <ctime>



Date::Date()
{
	this->_day = 1;
	this->_month = 1;
	this->_year = 1;
}

Date::Date(int day, int month, int year)
{
	this->_day = day;
	this->_month = month;
	this->_year = year;
}

Date::~Date()
{

}

int Date::getDay()
{
	return this->_day;
}

int Date::getMonth()
{
	return this->_month;
}

int Date::getYear()
{
	return this->_year;
}

void Date::setDay(int day)
{
	this->_day = day;
}

void Date::setMonth(int month)
{
	this->_month = month;
}

void Date::setYear(int year)
{
	this->_year = year;
}

Date Date::getToday()
{
	time_t now = time(0);
	tm localTime;
	localtime_s(&localTime, &now);
	int day = localTime.tm_mday;
	int month = localTime.tm_mon + 1;
	int year = localTime.tm_year + 1900;
	return Date(day, month, year);
}

#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

struct Date 
{
	int m_month; //the date's month
	int m_day; //the date's day
	int m_year; //the date's year

	Date(); //creates a blanke date, or 01/01/1
	Date(int date[3]); //creates a date with the given ints
	Date(int month, int day, int year); //creates a date with the given ints

	friend std::ostream& operator<<(std::ostream& os, const Date& dt); //sends the toString of Date to the ostream

	friend bool operator<(const Date& dt1, const Date& dt2); //basic relational operater overrides, does what you expect
	friend bool operator>(const Date& dt1, const Date& dt2);
	friend bool operator==(const Date& dt1, const Date& dt2);
	friend bool operator!=(const Date& dt1, const Date& dt2);
	friend bool operator<=(const Date& dt1, const Date& dt2);
	friend bool operator>=(const Date& dt1, const Date& dt2);

	int operator[](int index); //returns one of the three variables, month for 0, day for 1, year for 2

	std::string toString() const; //returns a string consisting of month/day/year
};

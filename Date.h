#pragma once
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

struct Date 
{
	int m_month;
	int m_day;
	int m_year;

	Date();
	Date(int date[3]);
	Date(int month, int day, int year);

	friend std::ostream& operator<<(std::ostream& os, const Date& dt);

	friend bool operator<(const Date& dt1, const Date& dt2);
	friend bool operator>(const Date& dt1, const Date& dt2);
	friend bool operator==(const Date& dt1, const Date& dt2);
	friend bool operator!=(const Date& dt1, const Date& dt2);
	friend bool operator<=(const Date& dt1, const Date& dt2);
	friend bool operator>=(const Date& dt1, const Date& dt2);

	int operator[](int index);

	std::string toString() const;
};

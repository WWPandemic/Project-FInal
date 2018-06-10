#pragma once
#include <iostream>
#include <string>

class Date 
{
private:
	int *date;
public:
	Date();
	Date(int date[3]);
	Date(int month, int day, int year);
	Date(const Date &);
	~Date();

	Date operator=(const Date &);
	friend std::ostream& operator<<(std::ostream& os, const Date& dt);
	friend bool operator==(const Date& dt1, const Date& dt2);
	friend bool operator!=(const Date& dt1, const Date& dt2);
	friend bool operator<(const Date& dt1, const Date& dt2);
	friend bool operator<=(const Date& dt1, const Date& dt2);
	friend bool operator>(const Date& dt1, const Date& dt2);
	friend bool operator>=(const Date& dt1, const Date& dt2);
	
	const int *getDate() const;
	void setDate(int date[3]);
	void setDate(int month, int day, int year);
	void setDate(const int *date);

	//static int compareDate(Date date1, Date date2);
	//static int compareDate(int month1, int day1, int year1, Date date2);
	//static int compareDate(Date date1, int month2, int day2, int year2);
	//static int compareDate(int month1, int day1, int year1, int month2, int day2, int year2);
	//int compareDate(Date date2);

	std::string toString() const;

};

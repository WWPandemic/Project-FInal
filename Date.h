#pragma once
#include <string>

class Date 
{
private:
	int date[3];
public:
	Date();
	Date(int month, int day, int year);
	int *getDate();
	void setDate(int month, int day, int year);
	int compare(Date other);
	std::string toString();
};

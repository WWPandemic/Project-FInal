#include "Date.h"

Date::Date() {
	*(date + 0) = 1;
	*(date + 1) = 1;
	*(date + 2) = 1;
}

Date::Date(int month, int day, int year) {
	*(date + 0) = month;
	*(date + 1) = day;
	*(date + 2) = year;
}

int *Date::getDate() {
	return date;
}

void Date::setDate(int month, int day, int year) {
	*(date + 0) = month;
	*(date + 1) = day;
	*(date + 2) = year;
}

int Date::compare(Date other) {
	int *date2 = other.getDate();
	if(*(date+0))
	return 0;
}

std::string Date::toString() {
	std::string str = "";
	if (*(date + 0) < 10)
		str.append("0");
	str.append(std::to_string(*(date + 0)));
	str.append("/");
	if (*(date + 1) < 10)
		str.append("0");
	str.append(std::to_string(*(date + 1)));
	str.append("/");
	str.append(std::to_string(*(date + 2)));
	return str;
}
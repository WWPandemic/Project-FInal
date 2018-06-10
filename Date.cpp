#include <iostream>
#include <ostream>
#include "Date.h"

Date::Date() {
	setDate(1, 1, 1);
}

Date::Date(int date[3]) {
	setDate(date);
}

Date::Date(int month, int day, int year) {
	setDate(month, day, year);
}

Date::Date(const Date &src) {
	setDate(src.getDate());
}

Date::~Date() {
	delete[]date;
}

Date Date::operator=(const Date &src) {
	setDate(src.getDate());
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Date& dt) {
	os << dt.toString();
	return os;
}

bool operator==(const Date& dt1, const Date& dt2) {
	const int *date1 = dt1.getDate(), *date2 = dt2.getDate();
	if (*(date1 + 0) == *(date2 + 0) && *(date1 + 1) == *(date2 + 1) && *(date1 + 2) == *(date2 + 2))
		return true;
	return false;
}

bool operator!=(const Date& dt1, const Date& dt2) {
	const int *date1 = dt1.getDate(), *date2 = dt2.getDate();
	if (*(date1 + 0) != *(date2 + 0) || *(date1 + 1) != *(date2 + 1) || *(date1 + 2) != *(date2 + 2))
		return true;
	return false;
}

bool operator<(const Date& dt1, const Date& dt2) {
	if (dt1 != dt2) {
		const int *date1 = dt1.getDate(), *date2 = dt2.getDate();
		if (*(date1 + 2) < *(date2 + 2))
			return true;
		else if (*(date1 + 2) == *(date2 + 2)) {
			if (*(date1 + 0) < *(date2 + 0))
				return true;
			else if (*(date1 + 0) == *(date2 + 0))
				if (*(date1 + 1) < *(date2 + 1))
					return true;
		}
	}
	return false;
}

bool operator<=(const Date& dt1, const Date& dt2) {
	if (dt1 == dt2 || dt1 < dt2)
		return true;
	return false;
}

bool operator>(const Date& dt1, const Date& dt2) {
	if (dt1 != dt2) {
		const int *date1 = dt1.getDate(), *date2 = dt2.getDate();
		if (*(date1 + 2) > *(date2 + 2))
			return true;
		else if (*(date1 + 2) == *(date2 + 2)) {
			if (*(date1 + 0) > *(date2 + 0))
				return true;
			else if (*(date1 + 0) == *(date2 + 0))
				if (*(date1 + 1) > *(date2 + 1))
					return true;
		}
	}
	return false;
}

bool operator>=(const Date& dt1, const Date& dt2) {
	if (dt1 == dt2 || dt1 > dt2)
		return true;
	return false;
}

const int *Date::getDate() const {
	return date;
}

void Date::setDate(int date[3]) {
	this->date = new int[3];
	*(this->date + 0) = date[0];
	*(this->date + 1) = date[1];
	*(this->date + 2) = date[2];
}

void Date::setDate(int month, int day, int year) {
	this->date = new int[3];
	*(this->date + 0) = month;
	*(this->date + 1) = day;
	*(this->date + 2) = year;
}

void Date::setDate(const int *date) {
	this->date = new int[3];
	*(this->date + 0) = date[0];
	*(this->date + 1) = date[1];
	*(this->date + 2) = date[2];
}

std::string Date::toString() const{
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
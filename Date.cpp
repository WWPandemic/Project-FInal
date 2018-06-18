#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"

Date::Date() : m_month(1), m_day(1), m_year(1) {}
Date::Date(int date[3]) : m_month(date[0]), m_day(date[1]), m_year(date[2]) {}
Date::Date(int month, int day, int year) : m_month(month), m_day(day), m_year(year) {}

std::ostream& operator<<(std::ostream& os, const Date& dt) { os << dt.toString(); return os; }

bool operator<(const Date& dt1, const Date& dt2) {
	if (dt1.m_year < dt2.m_year)
		return true;
	else if (dt1.m_year == dt2.m_year)
		if (dt1.m_month < dt2.m_month)
			return true;
		else if (dt1.m_month == dt2.m_month)
			if (dt1.m_day < dt2.m_day)
				return true;
	return false;

}

bool operator>(const Date& dt1, const Date& dt2) {
	if (dt1.m_year > dt2.m_year)
		return true;
	else if (dt1.m_year == dt2.m_year)
		if (dt1.m_month > dt2.m_month)
			return true;
		else if (dt1.m_month == dt2.m_month)
			if (dt1.m_day > dt2.m_day)
				return true;
	return false;
}

bool operator==(const Date& dt1, const Date& dt2) {
	if (dt1.m_year == dt2.m_year && dt1.m_month == dt2.m_month && dt1.m_day == dt2.m_day)
		return true;
	return false;
}

bool operator!=(const Date& dt1, const Date& dt2) {
	if (dt1 == dt2)
		return false;
	return true;
}

bool operator<=(const Date& dt1, const Date& dt2) {
	if (dt1 < dt2 || dt1 == dt2)
		return true;
	return false;
}

bool operator>=(const Date& dt1, const Date& dt2) {
	if (dt1 > dt2 || dt1 == dt2)
		return true;
	return false;
}

int Date::operator[](int index) {
	switch (index) {
	case 0:
		return m_month;
		break;
	case 1:
		return m_day;
		break;
	case 2:
		return m_year;
		break;
	default:
		exit(0);
	}
}

std::string Date::toString() const {
	std::ostringstream o;
	o << m_month << "/" << m_day << "/" << m_year;
	return o.str();
}
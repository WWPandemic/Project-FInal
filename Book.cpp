#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Book.h"

Book::Book() {
	m_title = "*";
	m_author = "*";
	m_publisher = "*";
	m_ISBN = 0;
	m_date = Date();
	m_quantity = 0;
	m_cost = 0;
	m_price = 0;
}

Book::Book(std::string title, std::string author, std::string publisher, int ISBN, Date date, int quantity, double cost, double price) {
	m_title = title;
	m_author = author;
	m_publisher = publisher;
	m_ISBN = ISBN;
	m_date = date;
	m_quantity = quantity;
	m_cost = cost;
	m_price = price;
}

std::ostream& operator<<(std::ostream& os, const Book& b) {
	int count = b.getQuantity();
	os << b.toString();
	return os;
}

std::istream& operator>>(std::istream& is, const Book& b) {
	return is;
}

bool operator==(const Book &b1, const Book &b2) {
	if (b1.getTitle() == b2.getTitle())
		if (b1.getAuthor() == b2.getAuthor())
			if(b1.getPublisher() == b2.getPublisher())
				if(b1.getDate() == b2.getDate())
					if(b1.getQuantity() == b1.getQuantity())
						if(b1.getCost() == b2.getCost())
							if(b1.getPrice() == b2.getPrice())
								return true;
	return false;
}

bool operator!=(const Book &b1, const Book &b2) {
	if (b1 == b2)
		return false;
	return true;
}

bool operator<(const Book &b1, const Book &b2) {
	if (b1.getTitle() < b2.getTitle())
		return true;
	else if (b1.getTitle() == b2.getTitle())
		if (b1.getAuthor() < b2.getAuthor())
			return true;
		else if (b1.getAuthor() == b2.getAuthor())
			if (b1.getPublisher() < b2.getPublisher())
				return true;
			else if (b1.getPublisher() == b2.getPublisher())
				if (b1.getISBN() < b2.getISBN())
					return true;
				else if (b1.getISBN() == b2.getISBN())
					if (b1.getDate() < b2.getDate())
						return true;
					else if (b1.getDate() == b2.getDate())
						if (b1.getQuantity() < b2.getQuantity())
							return true;
						else if (b1.getQuantity() == b2.getQuantity())
							if (b1.getCost() < b2.getCost())
								return true;
							else if (b1.getCost() == b2.getCost())
								if (b1.getPrice() < b2.getPrice())
									return true;
	return false;
}

bool operator<=(const Book &b1, const Book &b2) {
	if (b1 == b2 || b1 < b2)
		return true;
	return false;
}

bool operator>(const Book &b1, const Book &b2) {
	if(b1 < b2 || b1 == b2)
		return false;
	return true;
}

bool operator>=(const Book &b1, const Book &b2) {
	if(b1 < b2)
		return false;
	return true;
}
/*
- - - Getters
*/
std::string Book::getTitle() const{
	return m_title;
}

std::string Book::getAuthor() const{
	return m_author;
}

std::string Book::getPublisher() const{
	return m_publisher;
}

int Book::getISBN() const{
	return m_ISBN;
}

Date Book::getDate() const{
	return m_date;
}

int Book::getQuantity() const{
	return m_quantity;
}

double Book::getCost() const{
	return m_cost;
}

double Book::getPrice() const{
	return m_price;
}
/*
- - - Setters
*/
void Book::setTitle(std::string title) {
	this->m_title = title;
}

void Book::setAuthor(std::string author) {
	this->m_author = author;
}

void Book::setPublisher(std::string publisher) {
	this->m_publisher = publisher;
}

void Book::setISBN(int ISBN) {
	this->m_ISBN = ISBN;
}

void Book::setDate(Date date) {
	this->m_date = date;
}

void Book::setQuantity(int quantityOnHand) {
	this->m_quantity = quantityOnHand;
}

void Book::setCost(double wholesaleCost) {
	this->m_cost = wholesaleCost;
}

void Book::setPrice(double retailPrice) {
	this->m_price = retailPrice;
}

std::string Book::toString() const{
	std::ostringstream o;
	o << m_title
		<< " writen by " << m_author
		<< " published by " << m_publisher
		<< " with an ISBN of " << m_ISBN << std::endl;
	o << "\tAdded on " << m_date
		<< " with " << m_quantity << " copies in stock"
		<< " each costing $" << m_cost
		<< " and selling for $" << m_price;
	return o.str();
}

void Book::print() {
	std::cout << toString() << std::endl;
}

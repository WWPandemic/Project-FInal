#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Book.h"

Book::Book() {
	this->title = "*";
	this->author = "*";
	this->publisher = "*";
	this->ISBN = 0;
	this->dateAdded = Date();
	this->quantityOnHand = 0;
	this->wholesaleCost = 0;
	this->retailPrice = 0;
	this->sortBy = 1;
}

Book::Book(std::string title, std::string author, std::string publisher, int ISBN, Date dateAdded, int quantityOnHand, double wholesaleCost, double retailPrice) {
	this->title = title;
	this->author = author;
	this->publisher = publisher;
	this->ISBN = ISBN;
	this->dateAdded = dateAdded;
	this->quantityOnHand = quantityOnHand;
	this->wholesaleCost = wholesaleCost;
	this->retailPrice = retailPrice;
	this->sortBy = 1;
}

std::ostream& operator<<(std::ostream& os, const Book& b) {
	Book book = b;
	os << book.toString();
	return os;
}

std::istream& operator>>(std::istream& is, const Book& b) {
	return is;
}

bool operator==(const Book &book1, const Book &book2) {
	if (book1.getTitle() == book2.getTitle())
		if (book1.getAuthor() == book2.getAuthor())
			if(book1.getPublisher() == book2.getPublisher())
				if(book1.getDateAdded() == book2.getDateAdded())
					if(book1.getQuantityOnHand() == book1.getQuantityOnHand())
						if(book1.getWholesaleCost() == book2.getWholesaleCost())
							if(book1.getRetailPrice() == book2.getRetailPrice())
								return true;
	return false;
}

bool operator!=(const Book &book1, const Book &book2) {
	return true;
}

bool operator<(const Book &book1, const Book &book2) {
	return true;
}

bool operator<=(const Book &book1, const Book &book2) {
	return true;
}

bool operator>(const Book &book1, const Book &book2) {
	return true;
}

bool operator>=(const Book &book1, const Book &book2) {
	return true;
}

std::string Book::getTitle() const{
	return title;
}

std::string Book::getAuthor() const{
	return author;
}

std::string Book::getPublisher() const{
	return publisher;
}

int Book::getISBN() const{
	return ISBN;
}

Date Book::getDateAdded() const{
	return dateAdded;
}

int Book::getQuantityOnHand() const{
	return quantityOnHand;
}

double Book::getWholesaleCost() const{
	return wholesaleCost;
}

double Book::getRetailPrice() const{
	return retailPrice;
}

int Book::getSortBy() const {
	return sortBy;
}

void Book::setTitle(std::string title) {
	this->title = title;
}

void Book::setAuthor(std::string author) {
	this->author = author;
}

void Book::setPublisher(std::string publisher) {
	this->publisher = publisher;
}

void Book::setISBN(int ISBN) {
	this->ISBN = ISBN;
}

void Book::setDate(Date date) {
	this->dateAdded = date;
}

void Book::setQuantityOnHand(int quantityOnHand) {
	this->quantityOnHand = quantityOnHand;
}

void Book::setWholesaleCost(double wholesaleCost) {
	this->wholesaleCost = wholesaleCost;
}

void Book::setRetailPrice(double retailPrice) {
	this->retailPrice = retailPrice;
}

void Book::setSortBy(int sortBy) {
	this->sortBy = sortBy;
}

std::string Book::toString() const{
	std::string str = title + " " + author + " " + publisher;
	str.append(" " + std::to_string(ISBN));
	str.append(" " + dateAdded.toString());
	str.append(" " + std::to_string(quantityOnHand));
	str.append(" " + std::to_string(wholesaleCost));
	str.append(" " + std::to_string(retailPrice));
	return str;
}

void Book::print() {
	std::cout << this->toString() << std::endl;
}

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

}

bool operator!=(const Book &book1, const Book &book2) {

}

bool operator<(const Book &book1, const Book &book2) {

}

bool operator<=(const Book &book1, const Book &book2) {

}

bool operator>(const Book &book1, const Book &book2) {

}

bool operator>=(const Book &book1, const Book &book2) {

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
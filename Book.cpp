#include "Book.h"

Book::Book() {
	type = 1;
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
	type = 1;
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

Date Book::getDataAdded() const{
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

int Book::getType() const{
	return type;
}

std::string Book::toString() {
	std::string str = title + " " + author + " " + publisher;
	str.append(" " + std::to_string(ISBN));
	str.append(" " + dateAdded.toString());
	str.append(" " + std::to_string(quantityOnHand));
	str.append(" " + std::to_string(wholesaleCost));
	str.append(" " + std::to_string(retailPrice));
	return str;
}
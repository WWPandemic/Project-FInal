#pragma once
#include <string>
#include "Date.h"

class Book
{
protected:
	std::string title;
	std::string author;
	std::string publisher;
	int ISBN;
	Date dateAdded;
	int quantityOnHand;
	double wholesaleCost;
	double retailPrice;
public:
	Book();
	Book(std::string title, std::string author, std::string publisher, int ISBN, Date dateAdded, int quantityOnHand, double wholesaleCost, double retailPrice);
	
	friend std::ostream& operator<<(std::ostream& os, const Book& b);

	std::string getTitle() const;
	std::string getAuthor() const;
	std::string getPublisher() const;
	int getISBN() const;
	Date getDateAdded() const;
	int getQuantityOnHand() const;
	double getWholesaleCost() const;
	double getRetailPrice() const;
	std::string toString() const;
	void print();
};

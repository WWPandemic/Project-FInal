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
	int type;
public:
	Book();
	Book(std::string title, std::string author, std::string publisher, int ISBN, Date dateAdded, int quantityOnHand, double wholesaleCost, double retailPrice);
	std::string getTitle() const;
	std::string getAuthor() const;
	std::string getPublisher() const;
	int getISBN() const;
	Date getDataAdded() const;
	int getQuantityOnHand() const;
	double getWholesaleCost() const;
	double getRetailPrice() const;
	int getType() const;
	std::string toString();
};

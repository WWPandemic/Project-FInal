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
	//friend std::istream& operator>>(std::istream& is, const Book& b);
	friend bool operator==(const Book &book1, const Book &book2);
	friend bool operator!=(const Book &book1, const Book &book2);
	friend bool operator<(const Book &book1, const Book &book2);
	friend bool operator<=(const Book &book1, const Book &book2);
	friend bool operator>(const Book &book1, const Book &book2);
	friend bool operator>=(const Book &book1, const Book &book2);

	std::string getTitle() const;
	std::string getAuthor() const;
	std::string getPublisher() const;
	int getISBN() const;
	Date getDateAdded() const;
	int getQuantityOnHand() const;
	double getWholesaleCost() const;
	double getRetailPrice() const;

	void setTitle(std::string title);
	void setAuthor(std::string author);
	void setPublisher(std::string publisher);
	void setISBN(int ISBN);
	void setDate(Date date);
	void getQuantityOnHand(int quantityOnHand);
	void getWholesaleCost(double wholesaleCost);
	void getRetailPrice(double retailPrice);



	std::string toString() const;
	void print();
};

#pragma once
#include <string>
#include "Date.h"

class Book
{
protected:
	std::string m_title;
	std::string m_author;
	std::string m_publisher;
	int m_ISBN;
	Date m_date;
	int m_quantity;
	double m_cost;
	double m_price;
public:
	Book();
	Book(std::string title, std::string author, std::string publisher, int ISBN, Date date, int quantity, double cost, double price);
	
	friend std::ostream& operator<<(std::ostream& os, const Book& b);
	
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
	Date getDate() const;
	int getQuantity() const;
	double getCost() const;
	double getPrice() const;

	void setTitle(std::string title);
	void setAuthor(std::string author);
	void setPublisher(std::string publisher);
	void setISBN(int ISBN);
	void setDate(Date date);
	void setQuantity(int quantity);
	void setCost(double cost);
	void setPrice(double price);

	std::string toString() const;
	void print();
};

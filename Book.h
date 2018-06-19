#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <string>
#include "Date.h"

class Book
{
protected:
	std::string m_title; //The title of the Book
	std::string m_author; //The Author who wrote the Book
	std::string m_publisher; //The publisher that published the Book
	int m_ISBN; //The unique ISBN number the book has
	Date m_date; //The date the book was first added
	int m_quantity; //The number of books with these parameters
	double m_cost; //The cost each individual book the store buys
	double m_price; //The amount of money each books sells for
public:
	Book(); //creates an empty book
	Book(std::string title, std::string author, std::string publisher, int ISBN, Date date, int quantity, double cost, double price); //creates a book with the following parameters
	
	friend std::ostream& operator<<(std::ostream& os, const Book& b); //returns the toString() of the class to the given ostream
	
	friend bool operator==(const Book &book1, const Book &book2); //All of these overwrite the relational operators, does what you expect
	friend bool operator!=(const Book &book1, const Book &book2); 
	friend bool operator<(const Book &book1, const Book &book2);
	friend bool operator<=(const Book &book1, const Book &book2); 
	friend bool operator>(const Book &book1, const Book &book2); 
	friend bool operator>=(const Book &book1, const Book &book2);

	std::string getTitle() const; //returns the title of the book
	std::string getAuthor() const; //returns the author of the book
	std::string getPublisher() const; //returns the publisher of the book
	int getISBN() const; //returns the ISBN of the book
	Date getDate() const; //returns the date the book was added
	int getQuantity() const; //returns the number of books
	double getCost() const; //returns the cost of each book
	double getPrice() const; //returns the wholesale price of each book

	void setTitle(std::string title); //sets the title of the book
	void setAuthor(std::string author); //sets the author of the book
	void setPublisher(std::string publisher); //sets the publisher of the book
	void setISBN(int ISBN); //sets the ISBN of the book
	void setDate(Date date); //sets the date added of the book
	void setQuantity(int quantity); //sets the quantity of the book
	void setCost(double cost); //sets the cost of the book
	void setPrice(double price); //sets the wholesale price of the book

	std::string toString() const; //returns a two line string containing every parameter in book
	void print(); //sends the toString() of the book to cout
};

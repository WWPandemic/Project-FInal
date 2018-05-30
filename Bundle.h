#pragma once
#include <string>
#include "Book.h"

class Bundle
{
private:
	Book *buffer;
	int size;
	int max;
public:
	Bundle(int expectedMax);
	Bundle(const Bundle &src);
	~Bundle();

	Book *getBundle() const;
	int getSize() const;
	int getMax() const;
	void ensureSize(int size);
	void addBook(Book b);
	void addBook(std::string title, std::string author, std::string publisher, int ISBN, Date dateAdded, int quantityOnHand, double wholesaleCost, double retailPrice);
	void addBooks(Bundle books);
};
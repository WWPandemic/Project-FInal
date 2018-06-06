#pragma once
#include <string>
#include "Book.h"

class Bundle
{
private:
	Book *buffer;
	int arraySize;
	int arrayMax;
public:
	Bundle(int expectedMax);
	Bundle(const Bundle &src);
	~Bundle();

	friend std::ostream& operator<<(std::ostream& os, const Bundle& b);

	Book *getBundle() const;
	int getSize() const;

	void addBook(std::string title, std::string author, std::string publisher, int ISBN, Date dateAdded, int quantityOnHand, double wholesaleCost, double retailPrice);
	void addBook(Book b);
	void addBooks(Bundle books);

	void removeBook(int index);
	void removeBooks(Bundle books);
	void removeBooks(int minIndex, int maxIndex);
	void removeAll();

	void printBook(int index);
	void printAll();

	bool ensureSize(int size);
	bool ensureIndex(int index);
};
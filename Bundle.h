#pragma once
#include <string>
#include "Book.h"

class Bundle
{
private:
	Book *buffer;
	int arraySize;
	int arrayMax;
	int sortBy;
	
	int findPos(Book book);
	void sort();
public:
	void shuffle(int index, int num);
	void swap(Book &book1, Book &book2);

	Bundle();
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
	void removeBooks(int minIndex, int maxIndex);
	void removeBooks(Bundle books);
	void removeAll();
	void removeAllAfter(int index);

	void printBook(int index);
	void printAll();

	bool ensureSize(int size);
	bool ensureIndex(int index);

	void sortByProperty(int propertyNum);
};

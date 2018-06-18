#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Array.h"
#include "Book.h"

class Bundle {
protected:
	Array<Book> m_books;
	int m_size;

	int findPos(const Book &b);
public:
	Bundle();
	Bundle(int size);
	Bundle(const Bundle &);

	Book& operator[](int index) const;
	Bundle& operator=(const Bundle &);
	friend std::ostream& operator<<(std::ostream& os, const Bundle &);

	void addBook(std::string title, std::string author, std::string publisher, int ISBN, Date date, int quantity, double cost, double price);
	void addBook(const Book &);
	void addBooks(const Bundle &);

	void removeBook(int index);
	void removeBook(std::string title);
	void removeAll();
	void removeAll(std::string title);
	void removeAllAfter(int index);
	void removeAllAfter(std::string title);

	std::string getBookTitle(int index) const;
	std::string getBookAuthor(int index) const;
	std::string getBookPublisher(int index) const;
	int getBookISBN(int index) const;
	Date getBookDate(int index) const;
	int getBookQuantity(int index) const;
	double getBookCost(int index) const;
	double getBookPrice(int index) const;


	int getSize() const;
	
	int findFirstIndex(std::string title); //Returns the first book in the sorted array with the given name
	void findIndexBounds(std::string title, int index[2]);  //Returns a pair of indexs containing the lower and higher bound

	bool ensureIndex(int index) const;
	bool ensureSize(int size);

	void shuffle(int index, int num);

	Array<Book> getArray() const;
};
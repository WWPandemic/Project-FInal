#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Array.h"
#include "Book.h"

class Bundle {
protected:
	Array<Book> m_books; //the array of books the bundle has
	int m_size; //how many of the books the bundle has, since the array conatins some "blank" books

	int findPos(const Book &b); //finds the location a book sould be added in such that eveythign will be in order
public:
	Bundle(); //creates a standard bundle, with a default 25 book capacity in its array
	Bundle(int size); //creates a bundle with the given number of book capacity, still starts with zero actual books
	Bundle(const Bundle &); //creates a bundle with a copy of every book within the given bundle, with the array size being equal to the given bundle's active size

	Book& operator[](int index) const; //returns the book in the array within the bundle at the given idnex, assuming its a valud index
	Bundle& operator=(const Bundle &); //overwrite copy constructer, same as the copy constructer Bundle(cosnt Bundle &)
	friend std::ostream& operator<<(std::ostream& os, const Bundle &); //send all of the books within the Bundle to the ostream, up to the total size of the Bundle, (25 size array, 5 books actually used, 5 books are sent)

	void addBook(std::string title, std::string author, std::string publisher, int ISBN, Date date, int quantity, double cost, double price); //adds the given book to the Bundle (note the book is sorted as it is added, do not assume it will be added to the end)
	void addBook(const Book &); //adds the given book to the bundle (note the book is sorted as it is added, do not assume it will be added to the end)
	void addBooks(const Bundle &); //adds the contents of the given Bundle to this Bundle

	void removeBook(int index); //removes the book at the given index
	void removeBook(std::string title); //removes the first book in the array with the given title
	void removeAll(); //removes every book from the bundle, does not afect the array itself though
	void removeAll(std::string title); //removes every instance of book's with the given title
	void removeAllAfter(int index); //removes evey book from the bundle starting at the given index
	void removeAllAfter(std::string title); //removes every book from the bundle starting with the first book with the given title

	std::string getBookTitle(int index) const; //all of these take an index, and returns whatever spesified parameter
	std::string getBookAuthor(int index) const;
	std::string getBookPublisher(int index) const;
	int getBookISBN(int index) const;
	Date getBookDate(int index) const;
	int getBookQuantity(int index) const;
	double getBookCost(int index) const;
	double getBookPrice(int index) const;

	void setBookTitle(int index, std::string title); //all of these take an index, and set the specified parameter with the given variable
	void setBookAuthor(int index, std::string author);
	void setBookPublisher(int index, std::string publisher);
	void setBookISBN(int index, int ISBN);
	void setBookDate(int index, Date date);
	void setBookQuantity(int index, int quantity);
	void setBookCost(int index, double cost);
	void setBookPrice(int index,double price);

	int getSize() const; //returns the actual size of the bundle, not the size of the array within
	
	int findIndex(Book &); //returns the index of the first book that matched the provided
	int findFirstIndex(std::string title); //Returns the first book in the sorted array with the given name
	void findIndexBounds(std::string title, int index[2]);  //Returns a pair of indexs containing the lower and higher bound

	bool ensureIndex(int index) const; //returns true if the index is valid, false if not
	bool ensureSize(int size); //if the given int is larger that the array within bundle, expand that array to the given size

	Array<Book> getArray() const; //returns the array within bundle, use with caution
};
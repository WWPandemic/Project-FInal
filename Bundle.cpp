#define _CRT_SECURE_NO_WARNINGS
#include "Bundle.h"

Bundle::Bundle() : m_books(25) { m_size = 0; }  
Bundle::Bundle(int size) : m_books(size) { m_size = 0; } 
Bundle::Bundle(const Bundle &src) : m_books(src.getSize()) { 
	m_size = src.getSize();
	for (int i = 0; i < m_size; i++) //copys every book in src over to the newly comstructed bundle
		m_books[i] = src[i];
}

Bundle& Bundle::operator=(const Bundle& src) {  
	m_size = src.getSize();
	m_books = Array<Book>(m_size);
	for (int i = 0; i < m_size; i++) //copys every book in src over to the newly comstructed bundle
		m_books[i] = src[i];
	return *this;
}

Book& Bundle::operator[](int index) const {
	return m_books[index];
}

std::ostream& operator<<(std::ostream& os, const Bundle& src) {
	int size = src.getSize();
	for (int i = 0; i < size; i++)
		os << src[i] << std::endl; //sends the book at the given index to the ostream
	return os;
}

void Bundle::addBook(const Book &b) { //Adds the given book to the array, such that everything is in alphabetical order by title
	m_books.ensureLength(m_size + 1);
	int pos = findPos(b);
	for (int i = m_size - 1; i >= pos; i--)
		m_books.swap(m_books[i], m_books[i + 1]);
	m_books[pos] = b;
	m_size++;
}

void Bundle::addBook(std::string title, std::string author, std::string publisher, int ISBN, Date date, int quantity, double cost, double price) {
	addBook(Book(title, author, publisher, ISBN, date, quantity, cost, price));
}

void Bundle::addBooks(const Bundle &b) {
	int size = b.getSize();
	for (int i = 0; i < size; i++)
		addBook(b[i]);
}

void Bundle::removeBook(int index) {
	if (ensureIndex(index))
		for (int i = index; i < m_size; i++) //swaps books around such that the book at the given index is pushed out of scope
			m_books.swap(m_books[i], m_books[i + 1]);
	m_size--;
}

void Bundle::removeBook(std::string title) {
	removeBook(findFirstIndex("e"));
}

void Bundle::removeAll() {
	m_size = 0;
}

void Bundle::removeAll(std::string title) {
	int index[2] = { 0, 0 };
	findIndexBounds(title,index);
	int dif = index[1] - index[0] + 1;
	for (int i = 0; i < dif; i++)
		removeBook(index[0]);
}

void Bundle::removeAllAfter(int index) {
	if (ensureIndex(index))
		m_size = index;
}

void Bundle::removeAllAfter(std::string title) {
	removeAllAfter(findFirstIndex(title));
}

std::string Bundle::getBookTitle(int index) const { if (ensureIndex(index)) return m_books[index].getTitle(); }
std::string Bundle::getBookAuthor(int index) const { if (ensureIndex(index)) return m_books[index].getAuthor(); }
std::string Bundle::getBookPublisher(int index) const { if (ensureIndex(index)) return m_books[index].getPublisher(); }
int Bundle::getBookISBN(int index) const { if (ensureIndex(index)) return m_books[index].getISBN(); }
Date Bundle::getBookDate(int index) const { if (ensureIndex(index)) return m_books[index].getDate(); }
int Bundle::getBookQuantity(int index) const { if (ensureIndex(index)) return m_books[index].getQuantity(); }
double Bundle::getBookCost(int index) const { if (ensureIndex(index)) return m_books[index].getCost(); }
double Bundle::getBookPrice(int index) const { if (ensureIndex(index)) return m_books[index].getPrice(); }

void Bundle::setBookTitle(int index, std::string title) { if (ensureIndex(index)) m_books[index].setTitle(title); }
void Bundle::setBookAuthor(int index, std::string author) { if (ensureIndex(index)) m_books[index].setAuthor(author); }
void Bundle::setBookPublisher(int index, std::string publisher) { if (ensureIndex(index)) m_books[index].setPublisher(publisher); }
void Bundle::setBookISBN(int index, int ISBN) { if (ensureIndex(index)) m_books[index].setISBN(ISBN); }
void Bundle::setBookDate(int index, Date date) { if (ensureIndex(index)) m_books[index].setDate(date); }
void Bundle::setBookQuantity(int index, int quantity) { if (ensureIndex(index)) m_books[index].setQuantity(quantity); }
void Bundle::setBookCost(int index, double cost) { if (ensureIndex(index)) m_books[index].setCost(cost); }
void Bundle::setBookPrice(int index, double price) { if (ensureIndex(index)) m_books[index].setPrice(price); }

int Bundle::getSize() const {
	return m_size;
}

//this method is modified binary search
//instead of finding the index of a match (or lack their of)
//it instead finds the pos of where the book sould slot into the array (such that everything is in order)
//smaller than the book at the returned index, larger than the book at the index-1
//Thus when working correctly, every book should be in order at all times, and as such a dedicated sort method is not needed for bundle
int Bundle::findPos(const Book &b) { 
	int min = 0, middle = 0, max = m_size;
	while (min <= max) {
		middle = (min + max) / 2;
		if (b < m_books[middle])
			if (middle == 0 || b > m_books[middle - 1])
				return middle;
			else
				max = middle - 1;
		else if (b == m_books[middle])
			return middle;
		else
			min = middle + 1;
	}
	return m_size;
}

int Bundle::findIndex(Book &b) {
	int min = 0, middle = 0, max = m_size - 1; //Basic binary search algorithm
	while (min <= max) {
		middle = (min + max) / 2;
		if (b == m_books[middle]) { //if a match is found
			return middle; //return the index
		}
		else if (b < m_books[middle])
			max = middle - 1;
		else
			min = middle + 1;
	}
	return -1; //if no match is found at all, returns -1;
}

//returns the first index location of a book with the given title
int Bundle::findFirstIndex(std::string title) {
	int min = 0, middle = 0, max = m_size - 1; //general binary search algorithm
	while (min <= max) {
		middle = (min + max) / 2;
		if (title == m_books[middle].getTitle()) {
			for (; middle - 1 >= 0 && m_books[middle - 1].getTitle() == title; middle--); //moving the index to the lower bound
			return middle;
		}
		else if (title < m_books[middle].getTitle())
			max = middle - 1;
		else
			min = middle + 1;
	}
	return middle;
}
//its odd, but takes in an int[2] array along with the title being searched for, as otherwise it could potentially cause memory leaks
void Bundle::findIndexBounds(std::string title, int index[2]) {
	int min = 0, middle = 0, max = m_size - 1; //other than the for loops, this is a regualr binary search
	while (min <= max) {
		middle = (min + max) / 2;
		if (title == m_books[middle].getTitle()) {
			for (index[0] = middle; index[0] - 1 >= 0 && m_books[index[0] - 1].getTitle() == title; index[0]--); //this will become the index of the lower bound
			for (index[1] = middle; index[1] + 1 < m_size && m_books[index[1] + 1].getTitle() == title; index[1]++); //this will become the index of the higher bound
			break;
		}
		else if (title < m_books[middle].getTitle())
			max = middle - 1;
		else
			min = middle + 1;
	}
}

bool Bundle::ensureIndex(int index) const {
	if (index >= 0 && index < m_size) //checking to see if the index is greater than or equal to zero, or less then the size of the bundle
		return true;
	return false;
}

bool Bundle::ensureSize(int size) {
	if (size > m_books.getLength()) { //checking if the size is larger than size of the array
		m_books.reSize(size); //resizing the array to the new size
		return true;
	}
	return false;
}

Array<Book> Bundle::getArray() const {
	return m_books;
}
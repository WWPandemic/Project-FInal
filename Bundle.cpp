#define _CRT_SECURE_NO_WARNINGS
#include "Bundle.h"

Bundle::Bundle() : m_books(25) { m_size = 0; }
Bundle::Bundle(int size) : m_books(size) { m_size = 0; }
Bundle::Bundle(const Bundle &src) : m_books(src.getSize()) {
	m_size = src.getSize();
	for (int i = 0; i < m_size; i++)
		m_books[i] = src[i];
}

Bundle& Bundle::operator=(const Bundle& src) {
	int size = src.getSize();
	m_books = Array<Book>(size);
	for (int i = 0; i < size; i++)
		m_books[i] = src[i];
	return *this;
}

Book& Bundle::operator[](int index) const {
	return m_books[index];
}

std::ostream& operator<<(std::ostream& os, const Bundle& src) {
	int size = src.getSize();
	for (int i = 0; i < size; i++)
		os << src[i] << std::endl;
	return os;
}

void Bundle::addBook(const Book &b) {
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
		for (int i = index; i < m_size; i++)
			m_books.swap(m_books[i], m_books[i + 1]);
	m_size--;
}

void Bundle::removeAll() {
	m_size = 0;
}

void Bundle::removeAllAfter(int index) {
	if (ensureIndex(index))
		m_size = index;
}

std::string Bundle::getBookTitle(int index) const { if (ensureIndex(index)) return m_books[index].getTitle(); }
std::string Bundle::getBookAuthor(int index) const { if (ensureIndex(index)) return m_books[index].getAuthor(); }
std::string Bundle::getBookPublisher(int index) const { if (ensureIndex(index)) return m_books[index].getPublisher(); }
int Bundle::getBookISBN(int index) const { if (ensureIndex(index)) return m_books[index].getISBN(); }
Date Bundle::getBookDate(int index) const { if (ensureIndex(index)) return m_books[index].getDate(); }
int Bundle::getBookQuantity(int index) const { if (ensureIndex(index)) return m_books[index].getQuantity(); }
double Bundle::getBookCost(int index) const { if (ensureIndex(index)) return m_books[index].getCost(); }
double Bundle::getBookPrice(int index) const { if (ensureIndex(index)) return m_books[index].getPrice(); }

int Bundle::getSize() const {
	return m_size;
}

//this method is essentially a reverse binary search
//instead of finding the index of a match (or lack their of)
//it instead finds the pos of where the book sould slot into the array (such that everything is in order)
//Thus when working correctly, everything sould be in order at all times, and a dedicated sort method is not needed for bundle
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

//returns an index location of a book with the given title
int Bundle::findFirstIndex(std::string title) {
	int min = 0, middle = 0, max = m_size - 1;
	while (min <= max) {
		middle = (min + max) / 2;
		if (title == m_books[middle].getTitle()) {
			for (; middle - 1 >= 0 && m_books[middle - 1].getTitle() == title; middle--);
			return middle;
		}
		else if (title < m_books[middle].getTitle())
			max = middle - 1;
		else
			min = middle + 1;
	}
	return middle;
}

void Bundle::findIndexBounds(std::string title, int index[2]) {
	int min = 0, middle = 0, max = m_size - 1;
	while (min <= max) {
		middle = (min + max) / 2;
		if (title == m_books[middle].getTitle()) {
			for (index[0] = middle; index[0] - 1 >= 0 && m_books[index[0] - 1].getTitle() == title; index[0]--);
			for (index[1] = middle; index[1] + 1 < m_size && m_books[index[1] + 1].getTitle() == title; index[1]++);
			break;
		}
		else if (title < m_books[middle].getTitle())
			max = middle - 1;
		else
			min = middle + 1;
	}
}

bool Bundle::ensureIndex(int index) const {
	if (index >= 0 && index < m_size)
		return true;
	else {
		std::ostringstream o;
		o << "The index: " << index << " is out of bounds";
		throw o.str();
	}
}

bool Bundle::ensureSize(int size) {
	if (size > m_books.getLength()) {
		m_books.reSize(size);
		return true;
	}
	return false;
}

Array<Book> Bundle::getArray() const {
	return m_books;
}

void Bundle::shuffle(int index, int num) {
	if (m_books.ensureIndex(index)) {
		m_books.ensureLength(m_size + num);
		for (int i = m_size-1; i >= index; i--)
			m_books.swap(m_books[i], m_books[i + num]);
			//std::cout << i << " " << i + num << std::endl;
		m_size += num;
	}
	else {
		std::cout << "Yeah, something went wrong" << std::endl;
	}
}
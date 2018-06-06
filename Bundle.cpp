#include <iostream>
#include "Bundle.h"

Bundle::Bundle(int expectedMax) {
	this->arrayMax = expectedMax;
	buffer = new Book[arrayMax];
	arraySize = 0;
}

Bundle::Bundle(const Bundle &src) {
	this->arrayMax = src.getSize();
	buffer = new Book[arrayMax];
	addBooks(src);
}

Bundle::~Bundle() {
	delete[]buffer;
}

std::ostream& operator<<(std::ostream& os, const Bundle& b) {
	Book *buffer = b.getBundle();
	int arraySize = b.getSize();
	for (int i = 0; i < arraySize; i++)
		os << *(buffer + i) << std::endl;
	return os;
}

Book *Bundle::getBundle() const {
	return buffer;
}

int Bundle::getSize() const {
	return arraySize;
}

void Bundle::addBook(Book b) {
	ensureSize(arraySize + 1);
	*(buffer + arraySize) = b;
	arraySize++;
}

void Bundle::addBook(std::string title, std::string author, std::string publisher, int ISBN, Date dateAdded, int quantityOnHand, double wholesaleCost, double retailPrice) {
	Book b(title, author, publisher, ISBN, dateAdded, quantityOnHand, wholesaleCost, retailPrice);
	addBook(b);
}

void Bundle::addBooks(Bundle books) {
	int cpySize = books.getSize();
	Book *buffer2 = books.getBundle();
	ensureSize(arraySize + cpySize);
	if (arraySize+cpySize < arrayMax) {
		for (int i = 0; i < cpySize;i++) {
			addBook(*(buffer2 + i));
		}
		arraySize += cpySize;
	}
}

void Bundle::removeBook(int index) {
	if (ensureIndex(index)) {

	}
}

void Bundle::removeBooks(Bundle books) {

}

void Bundle::removeBooks(int minIndex, int maxIndex) {

}

void Bundle::removeAll() {
	delete[]buffer;
	buffer = new Book[arrayMax];
}


void Bundle::printBook(int index) {
	std::cout << (buffer + index)->toString() << std::endl;
}

void Bundle::printAll() {
	for (int i = 0; i < arraySize; i++)
		std::cout << (buffer + i)->toString() << std::endl;
}

bool Bundle::ensureSize(int size) {
	if (size >= arrayMax) {
		Book *buffer2 = new Book[size];
		for (int i = 0; i < arraySize; i++)
			*(buffer2 + i) = *(buffer + i);
		delete []buffer;
		buffer = buffer2;
		return false;
	}
	return true;
}

bool Bundle::ensureIndex(int index) {
	if (index < 0 || index > arraySize-1)
		return false;
	return true;
}
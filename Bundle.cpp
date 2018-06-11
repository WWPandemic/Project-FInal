#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Bundle.h"


Bundle::Bundle() {
	this->arrayMax = 5;
	buffer = new Book[arrayMax];
	arraySize = 0;
	sortBy = 1;
}

Bundle::Bundle(int expectedMax) {
	this->arrayMax = expectedMax;
	buffer = new Book[arrayMax];
	arraySize = 0;
	sortBy = 1;
}

Bundle::Bundle(const Bundle &src) {
	this->arrayMax = src.getSize();
	buffer = new Book[arrayMax];
	addBooks(src);
	sortBy = 1;
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
	int pos = findPos(b);
	b.setSortBy(sortBy);
	for (int i = arraySize; i >= pos; i--)
		swap(*(buffer + i), *(buffer + i + 1));
	swap(b, *(buffer + pos));
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
		for (int i = index; i < arraySize - 1; i++)
			swap(*(buffer + i), *(buffer + i + 1));
			//std::cout << i << " " << i + 1 << std::endl;
		arraySize--;
	}
}

void Bundle::removeBooks(int minIndex, int maxIndex) {
	if (ensureIndex(minIndex) && ensureIndex(maxIndex)) {
		int dif = maxIndex - minIndex;
		for (int i = 0; i <= dif; i++)
			removeBook(minIndex);
	}
}

void Bundle::removeBooks(Bundle books) {

}

void Bundle::removeAll() {
	arraySize = 0;
}

void Bundle::removeAllAfter(int index) {
	if (ensureIndex(index))
		arraySize = index;
}

void Bundle::printBook(int index) {
	std::cout << (buffer + index)->toString() << std::endl;
}

void Bundle::printAll() {
	for (int i = 0; i < arraySize; i++)
		std::cout << (buffer + i)->toString() << std::endl;
}

void Bundle::shuffle(int index, int num) {
	if (index != arraySize) {
		ensureSize(arraySize + num);
		if (num > 0)
			for (int i = arraySize; i >= index; i--)
				swap(*(buffer + i), *(buffer + i + num));
				//std::cout << i << " " << i + num << std::endl;
		else if(num < 0)
			for (int i = 0; i < num; i++)
				swap(*(buffer + arraySize - i), *(buffer));
		arraySize += num;
	}
}

void Bundle::swap(Book &book1, Book &book2) {
	Book temp = book1;
	book1 = book2;
	book2 = temp;
}

int Bundle::findPos(Book book) {
	int pos = arraySize;
	int min = 0;
	int max = arraySize;
	return pos;
}

bool Bundle::ensureSize(int size) {
	if (size >= arrayMax) {
		Book *buffer2 = new Book[size];
		for (int i = 0; i < arraySize; i++)
			swap(*(buffer2 + i),*(buffer + i));
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

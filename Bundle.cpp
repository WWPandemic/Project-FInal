#include "Bundle.h"

Bundle::Bundle(int expectedMax) {
	buffer = new Book[expectedMax];
	size = 0;
}

Bundle::Bundle(const Bundle &src) {
	
}

Bundle::~Bundle() {
	delete[]buffer;
}

Book *Bundle::getBundle() const {
	return buffer;
}

int Bundle::getSize() const {
	return size;
}

int Bundle::getMax() const {
	return max;
}

void Bundle::ensureSize(int size) {
	if(this->size < size)

}
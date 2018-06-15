#include "Bundle.h"

Bundle::Bundle() : m_size(0), m_books(25) {}

Bundle::Bundle(int size) : m_size(0), m_books(size) {}

Bundle::Bundle(const Bundle &src) : m_size(src.getLength()), m_books(m_size) {
	for (int i = 0; i < m_size; i++)
		m_books.swap(m_books[i],src[i]);
}

Book& Bundle::operator[](int index) const {
	int max = m_books.getLength();
	if (index >= 0 && index < max)
		return m_books[index];
	else
		exit(0);
}

int Bundle::getLength() const{
	return m_size;
}

Array<Book> Bundle::getArray() const {
	return m_books;
}
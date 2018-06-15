#pragma once
#include "Array.h"
#include "Book.h"

class Bundle {
private:
	Array<Book> m_books;
	int m_size;
public:
	Bundle();
	Bundle(int size);
	Bundle(const Bundle &src);

	Book& operator[](int index) const;

	int getLength() const;
	Array<Book> getArray() const;
};
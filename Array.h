#define _CRT_SECURE_NO_WARNINGS
#pragma once

template <typename T>
class Array {
private:
	T * m_data;
	int m_length;
public:
	Array() {
		m_data = 0;
		m_length = 0;
	}

	Array(int nSize) {
		m_data = new T[nSize];
		m_length = nSize;
	}

	Array(const Array &src) {
		m_length = src.getLength();
		m_data = new T[m_length];
		for (int i = 0; i < m_length; i++)
			*(m_data + i) = src[i];
	}

	~Array() {
		delete[] m_data;
	}

	void erase() {
		delete[] m_data;
		m_data = 0;
		m_length = 0;
	}

	T& operator[](int index) const {
		if (index >= 0 && index < m_length)
			return *(m_data + index);
		else {
			std::cout << "An improper index was used: " << index << std::endl;
			exit(0);
		}
	}

	Array& operator=(const Array &src) {
		m_length = src.getLength();
		m_data = new T[m_length];
		for (int i = 0; i < m_length; i++)
			*(m_data + i) = src[i];
		return *this;
	}

	void add(const T& obj, int index) {
		if (ensureIndex(index))
			this[index] = obj;
	}

	int findIndex(T* obj) {
		return 0;
	}

	int getLength() const { return m_length; }

	void ensureLength(int length) {
		if (length > m_length)
			reSize(length);
	}

	bool ensureIndex(int index) { return (index >= 0 && index < m_length); }

	void reSize(int size) {
		int max = (m_length < size ? m_length : size);
		T *data = new T[size];
		m_length = size;
		for (int i = 0; i < max; i++)
			swap(*(m_data + i), *(data + i));
		delete [] m_data;
		m_data = data;
	}

	void swap(T &t1, T &t2) {
		T temp = t1;
		t1 = t2;
		t2 = temp;
	}
};
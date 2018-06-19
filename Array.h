#define _CRT_SECURE_NO_WARNINGS
#pragma once

template <typename T>
class Array {
private:
	T * m_data; //points to a variably lengthed array created in the constructer
	int m_length; //the length of the array in question
public:
	Array() {
		m_data = 0; //the pointer points to nothing
		m_length = 0; //the size is likewise nothing
	}

	Array(int nSize) { //creates an array of the given size
		m_data = new T[nSize]; //the ponter is set to an array on the heap
		m_length = nSize; //the size of the array is saved
	}

	Array(const Array &src) { //creates a copy of the given array
		m_length = src.getLength(); //the size of the given array is copyed
		m_data = new T[m_length]; //the pointer is set to an equivalently sized array
		for (int i = 0; i < m_length; i++) //the contents of the given array is copied over to the newly created one
			*(m_data + i) = src[i];
	}

	~Array() { //overrided delete funtion, since the array is stored in the heap and can thus become a memory leak
		delete[] m_data;
	}

	void erase() { //deletes the contents of the array, and sets both the pointer and the length to 0
		delete[] m_data;
		m_data = 0;
		m_length = 0;
	}

	T& operator[](int index) const { //returns the object at the given index in the array
		if (index >= 0 && index < m_length) //if the index is vaild, procede
			return *(m_data + index);
		else { //else, throw an error to let the user know something went wrong
			std::cout << "An improper index was used: " << index << std::endl;
			exit(0);
		}
	}

	Array& operator=(const Array &src) { //creates a copy of the given array
		m_length = src.getLength(); //the length of the new array is set equal to the length of the given array
		m_data = new T[m_length]; //the pointer is set to a new array, the size of which equal to the given array
		for (int i = 0; i < m_length; i++) //the contents of the given array is copyed into the newly created one
			*(m_data + i) = src[i];
		return *this; // the newly created array is returned
	}

	void add(const T& obj, int index) { //replaces the object at the given index with the given object
		if (ensureIndex(index))
			this[index] = obj;
	}

	int getLength() const { return m_length; } //returns the length of the array

	void ensureLength(int length) { //if the given size is larger than the length of the array, resize the array to the given size
		if (length > m_length)
			reSize(length);
	}

	bool ensureIndex(int index) { return (index >= 0 && index < m_length); } //returns whether or not the index is valid

	void reSize(int size) { //creates a new internal array and copys the contents of the old one over
		int max = (m_length < size ? m_length : size); //max is set to the old size or given size depending on which is smaller, to prevent axcess violations
		T *data = new T[size]; //a new internal array is created
		m_length = size;
		for (int i = 0; i < max; i++) //contents are copyed
			swap(*(m_data + i), *(data + i));
		delete [] m_data; //old array is deleted
		m_data = data; //newly created array is now being pointed to
	}

	void swap(T &t1, T &t2) { //swaps the two given objects address locations
		T temp = t1;
		t1 = t2;
		t2 = temp;
	}
};
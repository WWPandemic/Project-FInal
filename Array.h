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
		else
			exit(0);
	}

	Array& operator=(const Array &src) {
		std::cout << "Copying array" << std::endl;
		m_length = src.getLength();
		m_data = new T[m_length];
		for (int i = 0; i < m_length; i++)
		{
			*(m_data + i) = src[i];
		}
		return *this;
	}

	void swap(T &t1, T &t2) {
		T temp = t1;
		t1 = t2;
		t2 = temp;
	}

	void reSize(int size) {
		T *data2 = new T[size];
		int max = (m_length > size ? m_length : size);
		for (int i = 0; i < max; i++)
			swap(m_data[i], data2[i]);
	}

	int getLength() const;
};

template <typename T>
int Array<T>::getLength() const { return m_length; }

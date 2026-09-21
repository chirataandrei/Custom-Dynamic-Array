#include "../include/Vector.hpp"
#include <cstring>
#include <stdexcept>
#include <algorithm>

namespace custom {

	Vector::Vector() : m_data(nullptr), m_size(0), m_capacity(0) {}

	Vector::Vector(size_t initial_capacity)
		: m_data(nullptr), m_size(0), m_capacity(initial_capacity) 
	{
		if (m_capacity > 0) {
			m_data = new int[m_capacity];
		}
	}

	Vector::~Vector() {
		delete[] m_data;
	}

	Vector::Vector(const Vector& other) : m_capacity(other.m_capacity), m_size(other.m_size), m_data(nullptr)
	{
		if (m_capacity > 0) {
			m_data = new int[m_capacity];
			std::memcpy(m_data, other.m_data, m_size * sizeof(int));
		}
	}

	Vector& Vector::operator=(const Vector& other) {
		if (this == &other) {
			return *this;
		}

		int* new_data = (other.m_capacity > 0) ? new int[other.m_capacity] : nullptr;
		if (new_data) {
			std::memcpy(new_data, other.m_data, other.m_size * sizeof(int));
		}
		delete[] m_data;
		m_data = new_data;
		m_size = other.m_size;
		m_capacity = other.m_capacity;

		return *this;
	}

	Vector::Vector(Vector &&other) noexcept : m_capacity(other.m_capacity), m_size(other.m_size), m_data(other.m_data)
	{
		other.m_data = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;
	}

	Vector& Vector::operator=(Vector&& other) noexcept {
		if (this == &other) {
			return *this;
		}

		delete[] m_data;
		m_data = other.m_data;
		m_size = other.m_size;
		m_capacity = other.m_capacity;

		other.m_data = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;

		return *this;
	}

	size_t Vector::size() const { return m_size; } 
	size_t Vector::capacity() const { return m_capacity; }
	bool Vector::empty() const { return (m_size == 0 ? true : false); }

	int& Vector::operator[](size_t index) { return *(m_data + index); }
	const int& Vector::operator[](size_t index) const { return *(m_data + index); }

	const int& Vector::at(size_t index) const {
		if (index >= m_size) {
			throw std::out_of_range("Vector index out of bounds");
		}
		return m_data[index];
	}

	int& Vector::at(size_t index) {
		if (index >= m_size) {
			throw std::out_of_range("Vector index out of bounds");
		}
		return m_data[index];
	}

	const int& Vector::front() const { return m_data[0]; };
	int& Vector::front() { return m_data[0]; };

	const int& Vector::back() const {return m_data[m_size - 1]; }
	int& Vector::back() {return m_data[m_size - 1]; }

	const int* Vector::data() const { return m_data; }
	int* Vector::data() { return m_data; }

	void Vector::reserve(size_t new_capacity) {
		if (new_capacity <= m_capacity) {
			return;
		}
		int* new_data = new int[new_capacity];
		if (m_size > 0) {
			memcpy(new_data, m_data, m_size * sizeof(int));
		}
		delete[] m_data;
		m_data = new_data;
		m_capacity = new_capacity;
	}

	void Vector::shrink_to_fit() {
		if (m_size == m_capacity) {
			return;
		}

		if (m_size == 0) {
			delete[] m_data;
			m_capacity = 0;
			return;
		}

		int* new_data = new int[m_size];
		std::memcpy(new_data, m_data, m_size * sizeof(int));
		delete[] m_data;
		m_data = new_data;
		m_capacity = m_size;
	}

	void Vector::resize(size_t new_size, int default_value) {
		if (m_size == new_size) {
			return;
		}

		if (new_size > m_size) {
			if (new_size > m_capacity) {
				reserve(new_size);
			}
			std::fill(m_data + m_size, m_data + new_size, default_value);
		}
		m_size = new_size;
	}

	void Vector::push_back(int value) {
		if (m_size == m_capacity) {
			reserve(2 * m_capacity);
			m_capacity *= 2;
		}
		m_data[m_size++] = value;
	}

	void Vector::pop_back() {
		if (empty()) {
        	throw std::out_of_range("Cannot pop_back from an empty vector");
    	}
    	--m_size;
	}

	void Vector::clear() {
		m_size = 0;
	}

	void Vector::insert(size_t index, int value) {
		if (index > m_size) {
			throw std::out_of_range("index out of range");
			return;
		}

		if (m_size == m_capacity) {
			reserve((m_capacity == 0) ? 1 : m_capacity * 2);
		}

		for (size_t i = m_size; i > index; --i) {
			m_data[i] = m_data[i - 1];
		}
		m_data[index] = value;
		m_size++;
	}

	void Vector::erase(size_t index) {
		if (index >= m_size) {
			throw std::out_of_range("index out of range");
			return;
		}

		if (m_size == 0) {
			return;
		}

		for (size_t i = m_size - 2; i >= index; i--) {
			m_data[i] = m_data[i + 1];
		}

		--m_size;
	}

	void Vector::swap(Vector& other) {
		std::swap(m_data, other.m_data);
		std::swap(m_size, other.m_size);
		std::swap(m_capacity, other.m_capacity);
	}

	const int* Vector::begin() const { return m_data; }
	int* Vector::begin() { return m_data; }
	const int* Vector::end() const { return m_data + m_size; }
	int* Vector::end() { return m_data + m_size; }
}
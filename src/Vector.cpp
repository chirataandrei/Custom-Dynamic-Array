#include "../include/Vector.hpp"
#include <cstring>
#include <stdexcept>

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
}
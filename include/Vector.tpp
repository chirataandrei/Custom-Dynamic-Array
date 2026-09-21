#include "Vector.hpp"
#include <cstring>
#include <stdexcept>
#include <algorithm>

namespace custom {

	template<typename T>
	Vector<T>::Vector() : m_data(nullptr), m_size(0), m_capacity(0) {}

	template<typename T>
	Vector<T>::Vector(size_t initial_capacity)
		: m_data(nullptr), m_size(0), m_capacity(initial_capacity) 
	{
		if (m_capacity > 0) {
			m_data = new T[m_capacity];
		}
	}

	template<typename T>
	Vector<T>::~Vector() {
		delete[] m_data;
	}

	template<typename T>
	Vector<T>::Vector(const Vector<T>& other) : m_capacity(other.m_capacity), m_size(other.m_size), m_data(nullptr)
	{
		if (m_capacity > 0) {
			m_data = new T[m_capacity];
			std::copy(other.m_data, other.m_data + other.m_size, m_data);
		}
	}

	template<typename T>
	Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
		if (this == &other) {
			return *this;
		}

		T* new_data = (other.m_capacity > 0) ? new T[other.m_capacity] : nullptr;
		if (new_data) {
			std::copy(other.m_data, other.m_data + other.m_size, new_data);
		}
		delete[] m_data;
		m_data = new_data;
		m_size = other.m_size;
		m_capacity = other.m_capacity;

		return *this;
	}

	template<typename T>
	Vector<T>::Vector(Vector<T> &&other) noexcept : m_capacity(other.m_capacity), m_size(other.m_size), m_data(other.m_data)
	{
		other.m_data = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;
	}

	template<typename T>
	Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept {
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

	template<typename T>
	size_t Vector<T>::size() const { return m_size; } 
	template<typename T>
	size_t Vector<T>::capacity() const { return m_capacity; }
	template<typename T>
	bool Vector<T>::empty() const { return m_size == 0; }

	template<typename T>
	T& Vector<T>::operator[](size_t index) { return *(m_data + index); }
	template<typename T>
	const T& Vector<T>::operator[](size_t index) const { return *(m_data + index); }

	template<typename T>
	const T& Vector<T>::at(size_t index) const {
		if (index >= m_size) {
			throw std::out_of_range("Vector index out of bounds");
		}
		return m_data[index];
	}

	template<typename T>
	T& Vector<T>::at(size_t index) {
		if (index >= m_size) {
			throw std::out_of_range("Vector index out of bounds");
		}
		return m_data[index];
	}

	template<typename T>
	const T& Vector<T>::front() const { return m_data[0]; }
	template<typename T>
	T& Vector<T>::front() { return m_data[0]; }

	template<typename T>
	const T& Vector<T>::back() const {return m_data[m_size - 1]; }
	template<typename T>
	T& Vector<T>::back() {return m_data[m_size - 1]; }

	template<typename T>
	const T* Vector<T>::data() const { return m_data; }
	template<typename T>
	T* Vector<T>::data() { return m_data; }

	template<typename T>
	void Vector<T>::reserve(size_t new_capacity) {
		if (new_capacity <= m_capacity) {
			return;
		}
		T* new_data = new T[new_capacity];
		if (m_size > 0) {
			std::copy(m_data, m_data + m_size, new_data);
		}
		delete[] m_data;
		m_data = new_data;
		m_capacity = new_capacity;
	}

	template<typename T>
	void Vector<T>::shrink_to_fit() {
		if (m_size == m_capacity) {
			return;
		}

		if (m_size == 0) {
			delete[] m_data;
			m_capacity = 0;
			m_data = nullptr;
			return;
		}

		T* new_data = new T[m_size];
		std::copy(m_data, m_data + m_size, new_data);
		delete[] m_data;
		m_data = new_data;
		m_capacity = m_size;
	}

	template<typename T>
	void Vector<T>::resize(size_t new_size, const T& default_value) {
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

	template<typename T>
	void Vector<T>::push_back(const T& value) {
		if (m_size == m_capacity) {
			reserve((m_capacity == 0) ? 1 : m_capacity * 2);
		}
		m_data[m_size++] = value;
	}

	template<typename T>
	void Vector<T>::push_back(T&& value) {
		if (m_size == m_capacity) {
        	reserve((m_capacity == 0) ? 1 : m_capacity * 2);
   		}
		m_data[m_size++] = std::move(value);
	}

	template<typename T>
	void Vector<T>::pop_back() {
		if (empty()) {
        	throw std::out_of_range("Cannot pop_back from an empty vector");
    	}
    	--m_size;
	}

	template<typename T>
	void Vector<T>::clear() {
		m_size = 0;
	}

	template<typename T>
	void Vector<T>::insert(size_t index, const T& value) {
		if (index > m_size) {
			throw std::out_of_range("index out of range");
			return;
		}

		if (m_size == m_capacity) {
			reserve((m_capacity == 0) ? 1 : m_capacity * 2);
		}

		for (size_t i = m_size; i > index; --i) {
			m_data[i] = std::move(m_data[i - 1]);
		}
		m_data[index] = value;
		m_size++;
	}

	template<typename T>
	void Vector<T>::insert(size_t index, T&& value) {
		if (index > m_size) {
			throw std::out_of_range("index out of range");
			return;
		}

		if (m_size == m_capacity) {
			reserve((m_capacity == 0) ? 1 : m_capacity * 2);
		}

		for (size_t i = m_size; i > index; --i) {
			m_data[i] = std::move(m_data[i - 1]);
		}
		m_data[index] = std::move(value);
		m_size++;
	}

	template<typename T>
	void Vector<T>::erase(size_t index) {
		if (index >= m_size) {
			throw std::out_of_range("index out of range");
			return;
		}

		if (m_size == 0) {
			return;
		}

		for (size_t i = index; i < m_size - 1; ++i) {
			m_data[i] = std::move(m_data[i + 1]);
		}

		--m_size;
	}

	template<typename T>
	void Vector<T>::swap(Vector<T>& other) {
		std::swap(m_data, other.m_data);
		std::swap(m_size, other.m_size);
		std::swap(m_capacity, other.m_capacity);
	}

	template<typename T>
	const T* Vector<T>::begin() const { return m_data; }
	template<typename T>
	T* Vector<T>::begin() { return m_data; }
	template<typename T>
	const T* Vector<T>::end() const { return m_data + m_size; }
	template<typename T>
	T* Vector<T>::end() { return m_data + m_size; }
}
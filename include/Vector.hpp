#pragma once

#include <cstddef>

namespace custom {
	class Vector {
		private:
			int* m_data;
			size_t m_size;
			size_t m_capacity;

		public:
			Vector();
			explicit Vector(size_t initial_capacity);
			~Vector();

			// copy constructor
			Vector(const Vector& other);
			// copy assignment
			Vector& operator=(const Vector& other);

			// move constructor
			Vector(Vector&& other) noexcept;
			// move assignment
			Vector& operator=(Vector&& other) noexcept;

			// state methods
			size_t size() const;
			size_t capacity() const;
			bool empty() const;
			int& operator[](size_t index);
			const int& operator[](size_t index) const;

			// element acces methods
			const int& at(size_t index) const;
			int& at(size_t index);
			const int& front() const;
			int& front();
			const int& back() const;
			int& back();
			const int* data() const;
			int* data();
			
			// capacity management
			void reserve(size_t new_capacity);
			void shrink_to_fit();
			void resize(size_t new_size, int default_value = 0);
			
			// modifiers
			void push_back(int value);
			void pop_back();
			void clear();
			void insert(size_t index, int value);
			void erase(size_t index);
			void swap(Vector &other);

			// support for iterators
			const int* begin() const;
			int* begin();
			const int* end() const;
			int* end();
	};	
}
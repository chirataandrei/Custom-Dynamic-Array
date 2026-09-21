#pragma once

#include <cstddef>

namespace custom {
	template <typename T>
	class Vector {
		private:
			T* m_data;
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
			T& operator[](size_t index);
			const T& operator[](size_t index) const;

			// element acces methods
			const T& at(size_t index) const;
			T& at(size_t index);
			const T& front() const;
			T& front();
			const T& back() const;
			T& back();
			const T* data() const;
			T* data();
			
			// capacity management
			void reserve(size_t new_capacity);
			void shrink_to_fit();
			void resize(size_t new_size, T default_value = 0);
			
			// modifiers
			void push_back(T value);
			void pop_back();
			void clear();
			void insert(size_t index, T value);
			void erase(size_t index);
			void swap(Vector &other);

			// support for iterators
			const T* begin() const;
			T* begin();
			const T* end() const;
			T* end();
	};	
}
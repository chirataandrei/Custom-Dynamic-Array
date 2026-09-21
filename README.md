# Custom Dynamic Array (`custom::Vector`)

A C++17 generic implementation of a dynamic array (similar to `std::vector` from the C++ Standard Library).

## Features

- **Template (Generic):** Supports any data type (`custom::Vector<T>`).
- **Memory Management:** Automatic reallocation, `reserve()`, `shrink_to_fit()`, `resize()`.
- **Copy & Move Semantics:** Complete implementation of Copy Constructor, Copy Assignment, Move Constructor, and Move Assignment.
- **Element Modifiers:** `push_back()`, `emplace_back()`, `pop_back()`, `insert()`, `erase()`, `clear()`, `swap()`.
- **Element Access:** Operator `[]`, `at()` (with bounds checking), `front()`, `back()`, `data()`.
- **Iterators:** Support for range-based `for` loops.

## Project Structure

```text
.
├── CMakeLists.txt
├── include/
│   ├── Vector.hpp    # Class declaration for custom::Vector
│   └── Vector.tpp    # Template method implementations
├── src/
│   └── main.cpp      # Main executable file
└── tests/
    └── test_vector.cpp # Unit tests
```

## Prerequisites

- C++ compiler with **C++17** support (g++, clang++, MSVC)
- **CMake** (version 3.14 or higher)

## Build and Run

1. **Create build directory and configure:**
   ```bash
   mkdir build
   cd build
   cmake ..
   ```

2. **Build:**
   ```bash
   make
   ```

3. **Run main executable:**
   ```bash
   ./main
   ```

4. **Run unit tests:**
   ```bash
   ./unit_tests
   ctest --output-on-failure
   ```

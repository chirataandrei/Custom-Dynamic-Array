cmake_minimum_required(VERSION 3.14)
project(CustomDynamicArray CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(main src/main.cpp)

enable_testing()
add_executable(unit_tests tests/test_vector.cpp)
add_test(NAME unit_tests COMMAND unit_tests)

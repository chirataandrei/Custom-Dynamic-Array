#include <cassert>
#include <iostream>
#include <string>
#include <stdexcept>
#include "Vector.hpp"

void test_constructors() {
    custom::Vector<int> v1;
    assert(v1.size() == 0);
    assert(v1.capacity() == 0);
    assert(v1.empty());

    custom::Vector<int> v2(10);
    assert(v2.size() == 0);
    assert(v2.capacity() == 10);
    assert(v2.empty());
}

void test_push_and_access() {
    custom::Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    assert(vec.size() == 3);
    assert(!vec.empty());
    assert(vec[0] == 1);
    assert(vec[1] == 2);
    assert(vec[2] == 3);
    assert(vec.at(0) == 1);
    assert(vec.at(1) == 2);
    assert(vec.at(2) == 3);
    assert(vec.front() == 1);
    assert(vec.back() == 3);

    bool exception_caught = false;
    try {
        vec.at(5);
    } catch (const std::out_of_range&) {
        exception_caught = true;
    }
    assert(exception_caught);
}

void test_copy_and_move() {
    custom::Vector<std::string> v1;
    v1.push_back("hello");
    v1.push_back("world");

    custom::Vector<std::string> v2 = v1;
    assert(v2.size() == 2);
    assert(v2[0] == "hello");
    assert(v2[1] == "world");

    custom::Vector<std::string> v3 = std::move(v1);
    assert(v3.size() == 2);
    assert(v3[0] == "hello");
    assert(v3[1] == "world");
    assert(v1.size() == 0);

    custom::Vector<std::string> v4;
    v4 = v2;
    assert(v4.size() == 2);
    assert(v4[0] == "hello");

    custom::Vector<std::string> v5;
    v5 = std::move(v2);
    assert(v5.size() == 2);
    assert(v5[0] == "hello");
}

void test_modifiers() {
    custom::Vector<int> vec;
    vec.push_back(10);
    vec.push_back(30);
    vec.insert(1, 20);

    assert(vec.size() == 3);
    assert(vec[0] == 10);
    assert(vec[1] == 20);
    assert(vec[2] == 30);

    vec.emplace_back(40);
    assert(vec.back() == 40);

    vec.erase(1);
    assert(vec.size() == 3);
    assert(vec[0] == 10);
    assert(vec[1] == 30);
    assert(vec[2] == 40);

    vec.pop_back();
    assert(vec.size() == 2);
    assert(vec.back() == 30);

    vec.clear();
    assert(vec.size() == 0);
    assert(vec.empty());
}

void test_capacity() {
    custom::Vector<int> vec;
    vec.reserve(50);
    assert(vec.capacity() >= 50);
    assert(vec.size() == 0);

    vec.push_back(1);
    vec.push_back(2);
    vec.shrink_to_fit();
    assert(vec.capacity() == 2);

    vec.resize(5, 99);
    assert(vec.size() == 5);
    assert(vec[2] == 99);
    assert(vec[4] == 99);

    vec.resize(2);
    assert(vec.size() == 2);
}

void test_swap_and_iterators() {
    custom::Vector<int> a;
    a.push_back(1);
    a.push_back(2);

    custom::Vector<int> b;
    b.push_back(10);

    a.swap(b);
    assert(a.size() == 1 && a[0] == 10);
    assert(b.size() == 2 && b[0] == 1 && b[1] == 2);

    int sum = 0;
    for (int val : b) {
        sum += val;
    }
    assert(sum == 3);
}

int main() {
    test_constructors();
    test_push_and_access();
    test_copy_and_move();
    test_modifiers();
    test_capacity();
    test_swap_and_iterators();

    std::cout << "All tests passed successfully!\n";
    return 0;
}

#include <iostream>
#include <string>
#include "Vector.hpp"

int main() {
    custom::Vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
	vec.push_back(40);

    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";

    vec.emplace_back(40);
    vec.insert(1, 15);

    for (int val : vec) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    vec.erase(2);
    vec.pop_back();

    std::cout << "Front: " << vec.front() << ", Back: " << vec.back() << "\n";
    std::cout << "Size: " << vec.size() << ", Capacity: " << vec.capacity() << "\n";

    vec.reserve(20);
    vec.shrink_to_fit();
    vec.resize(5, 100);

    custom::Vector<std::string> strVec;
    strVec.push_back("Hello");
    strVec.push_back("World");
    strVec.emplace_back("C++");

    for (const auto& str : strVec) {
        std::cout << str << " ";
    }
    std::cout << "\n";

    custom::Vector<std::string> copyVec = strVec;
    custom::Vector<std::string> moveVec = std::move(copyVec);

    strVec.swap(moveVec);
    strVec.clear();

    return 0;
}

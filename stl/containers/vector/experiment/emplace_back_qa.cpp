/**
 * @file emplace_back_qa.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-06-16
 *
 * @copyright Copyright (c) 2025
 *
 * @ref: https://andreasfertig.com/blog/2023/04/push_back-vs-emplace_back-when-to-use-what/
 *
 */

#include <vector>

#include "complex_widget.hpp"
#include "simple_widget.hpp"

int main(int argc, char const* argv[])
{
    std::vector<simple_widget> v;
    // v.reserve(5);

    std::cout << "capacity:" << v.capacity() << "\n";
    puts("- push_back");

    // B Using push\_back with a temporary object.
    v.push_back(simple_widget{3});

    puts("- emplace_back");

    // C Using emplace\_back with a temporary object.
    v.emplace_back(simple_widget{3});

    puts("- emplace_back");

    // D Using emplace\_back to create a new object.
    v.emplace_back(3);

    puts("-------");
    return 0;
}

/**
 * @file reference_optional.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-07-31
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * https://godbolt.org/z/araaefxT9
 * https://www.learncpp.com/cpp-tutorial/stdoptional/
 */

#include <functional>  // for std::reference_wrapper
#include <iostream>
#include <optional>
#include <string>

struct Employee
{
    std::string name{};  // expensive to copy
    int id;
    Employee() = default;
    Employee(std::string name, int id) : name(name), id(id) {}
    Employee(const Employee& e)
    {
        std::cout << "copy\n";
    }
};

void printEmployeeID(const std::optional<std::reference_wrapper<Employee>>& e = std::nullopt)
{
    if (e)
        std::cout << "Your ID number is " << e->get().id << ".\n";
    else
        std::cout << "Your ID number is not known.\n";
}

int main()
{
    printEmployeeID();  // we don't know the Employee yet

    Employee e{"James", 34};
    printEmployeeID(e);  // we know the Employee's ID now

    return 0;
}
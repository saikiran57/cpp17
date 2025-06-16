/**
 * @file custom_comparator.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-06-21
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * @brief https://rules.sonarsource.com/cpp/tag/since-c++14/RSPEC-6045/
 * https://www.fluentcpp.com/2017/06/09/search-set-another-type-key/
 *
 *
 */

#include <cctype>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <utility>

static void example1()
{
    std::map<std::string, int, std::less<>> m{{"abc", 1}, {"bbc", 2}, {"ccb", 3}};

    /*
      No more temporary std::string{"abc"}. if we use std::les<>
      When find is called, the STL essentially invokes

      std::less<void>::operator(std::string const& lhs, const char* rhs);
      This results in lhs < rhs. In other words, it compares the std::string
      against a C-style string with no undesired temporaries.
   */

    if (auto pos = m.find("abc"); pos != m.end())
    {
        std::cout << pos->first << ":" << pos->second << "\n";
    }
}

class Employee
{
public:
    Employee() = default;
    Employee(int id, std::string name) : m_id(id), m_name(std::move(name)) {}
    [[nodiscard]] int getId() const
    {
        return m_id;
    }

private:
    int m_id{};
    std::string m_name;
};

struct CustomComparator
{
    using t_IsTransparent = void;  // for example with void,
                                   // but could be int or struct CanSearchOnId;
    bool operator()(Employee const& employee1, Employee const& employee2) const
    {
        return employee1.getId() < employee2.getId();
    }
    bool operator()(int id, Employee const& employee) const
    {
        return id < employee.getId();
    }
    bool operator()(Employee const& employee, int id) const
    {
        return employee.getId() < id;
    }
};

static void transparentContainer()
{
    Employee const e;
    std::map<Employee, int, CustomComparator> m;

    m.emplace(Employee{1, "abc"}, 1);
    m.emplace(Employee{2, "bbc"}, 2);
    m.emplace(Employee{3333, "ccb"}, 3);

    std::cout << "custom Comparator:" << m.find(3333)->first.getId();
}

struct CaseInsensitiveCompare
{
    using t_IsTransparent = void;  // Enables heterogeneous operations.

    bool operator()(const std::string_view& lhs, const std::string_view& rhs) const
    {
        return std::ranges::lexicographical_compare(lhs, , rhs, , [](char l, char r) {
            return std::tolower(l) < std::tolower(r);
        });
    }
};

static void caseInsensitiveCompare()
{
    std::map<std::string, int, CaseInsensitiveCompare> m = {// Compliant
                                                            {"Dory", 1},
                                                            {"Marlin", 2},
                                                            {"Nemo", 3},
                                                            {"Emo", 4},
                                                            {"Darla", 5}};

    m.lower_bound("nemo");  // No more temporary std::string{"nemo"}.
}

int main()
{
    example1();
    transparentContainer();
    caseInsensitiveCompare();
    return 0;
}

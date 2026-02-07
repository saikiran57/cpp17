/**
 * @file map.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-06-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <map>
#include <string>

/*
 * https://www.geeksforgeeks.org/c-map-key-user-define-data-type/
 */
struct Abc
{
    std::string m_name;
    int m_a;

    // it must be overloaded and const
    bool operator<(const Abc& rhs) const
    {
        return this->m_a < rhs.m_a;
    }
};

static void mapFuncComplex()
{
    std::map<Abc, int> m;
    Abc const ob1{"abc", 1};
    Abc const ob2{"bbc", 2};
    Abc const ob3{"aaa", 3};

    m.insert({ob1, 1});
    m.insert({ob2, 2});
    m.insert({ob3, 3});

    for (auto [obj, val] : m)
    {
        std::cout << obj.m_a << ":" << obj.m_name << ":" << val << "\n";
    }

    auto pos = m.find(ob2);
    if (pos != m.end())
    {
        std::cout << "Value found: " << pos->first.m_a << ":" << pos->first.m_name << ":" << pos->second << "\n";
    }
}

// void mapFuncSimple()
// {
//     std::map<std::string, int> m;
//     m.insert({"abc", 1});
//     m.insert({"bbc", 2});
//     m.insert({"ccb", 3});

//     auto pos = m.find("abc");
//     if (pos != m.end());
//     {
//         std::cout << pos->first << ":" << pos->second << "\n";
//     }
// }

int main()
{
    mapFuncComplex();
    return 0;
}

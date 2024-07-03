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

/*
* https://www.geeksforgeeks.org/c-map-key-user-define-data-type/
*/
struct Abc{
    std::string name;
    int a;

    // it must be overloaded and const
    bool operator<(const Abc& rhs) const
    {
        return this->a < rhs.a;
    }
};

void mapFuncComplex()
{
    std::map<Abc, int> m;
    Abc ob1{"abc", 1};
    Abc ob2{"bbc", 2};
    Abc ob3{"aaa", 3};

    m.insert({ob1, 1});
    m.insert({ob2, 2});
    m.insert({ob3, 3});

    for (auto [obj, val] : m)
    {
        std::cout << obj.a << ":" << obj.name << ":" << val << "\n";
    }
    
    auto pos = m.find(ob2);
    if (pos != m.end());
    {
        std::cout << "Value found: " << pos->first.a << ":"<< pos->first.name << ":" << pos->second << "\n";
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
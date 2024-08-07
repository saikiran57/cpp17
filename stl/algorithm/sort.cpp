/**
 * @file sort.cpp
 * @author Saikiran Nadipilli
 * @brief 
 * @version 0.1
 * @date 2024-06-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <algorithm>
#include <vector>

template <typename T>
void print(const std::string_view sv, T &t)
{
    std::cout << sv;
    for (auto &&i : t)
    {
        std::cout << i << " ";    
    }
    std::cout << "\n";
}

void testFunc()
{
    std::vector<int> v{1,23,0,-1,-2};

    //standard sort incresing order
    std::sort(v.begin(), v.end());
    print("standard sort increasing:", v);

    //standard sort in non increasing order
    std::vector v2{2333,0,-222,4444,23};
    std::sort(v2.begin(), v2.end(), std::greater<>{});
    print("standard sort non increasing:", v2);

    //custom function object
    struct customLess
    {
        bool operator()(int a, int b)
        {
            return a < b;
        }
    };

    std::sort(v2.begin(), v2.end(), customLess());
    print("custom object", v2);

    //lambda call
    std::sort(v2.begin(), v2.end(), [](int a, int b){
        return a > b;
    });
    print("lambda call:", v2);
}

int main()
{
    testFunc();
    return 0;
}
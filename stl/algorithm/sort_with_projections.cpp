/**
 * @file sort_with_projections.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-06-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class MyObject
{
public:
    int property1;
    double property2;
    std::string property3;

    MyObject(int p1, double p2, const std::string& p3) : property1(p1), property2(p2), property3(p3) {}
};

void printVector(const std::vector<MyObject>& vec)
{
    for (const auto& obj : vec)
    {
        std::cout << "(" << obj.property1 << ", " << obj.property2 << ", " << obj.property3 << ") ";
    }
    std::cout << std::endl;
}

template <typename T, typename Projection>
void sortWithProjection(const std::vector<T>& vec, Projection proj)
{
    std::sort(vec.begin(), vec.end(), [&](const T& a, const T& b) {
        return proj(a) < proj(b);
    });
}

int main()
{
    std::vector<MyObject> vec = {MyObject(3, 2.5, "c"), MyObject(1, 3.5, "a"), MyObject(2, 1.5, "b")};

    // Sort by property1 using projection
    sortWithProjection(vec, [](const MyObject& obj) {
        return obj.property1;
    });
    std::cout << "Sorted by property1:" << std::endl;
    printVector(vec);

    // Sort by property2 using projection
    sortWithProjection(vec, [](const MyObject& obj) {
        return obj.property2;
    });
    std::cout << "Sorted by property2:" << std::endl;
    printVector(vec);

    // Sort by property3 using projection
    sortWithProjection(vec, [](const MyObject& obj) {
        return obj.property3;
    });
    std::cout << "Sorted by property3:" << std::endl;
    printVector(vec);

    return 0;
}

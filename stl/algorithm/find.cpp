
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    // find, find_if, find_if_not

    const auto v = {1, 2, 3, 4, 5};

    for (auto i : {3, 5})
    {
        // find element
        if (std::find(v.begin(), v.end(), i) != v.end())
        {
            std::cout << "element found\n";
        }
        else
        {
            std::cout << "element not found\n";
        }
    }

    // find_if only positive numbers
    const auto isEven = [](auto i) {
        return i % 2 == 0;
    };

    if (auto it = std::find_if(v.begin(), v.end(), isEven); it != v.end())
    {
        std::cout << "Even number: " << *it << std::endl;
    }

    // find_if_not
    const auto vec = {2, 4, 6, 8, 10, 11};

    if (auto it = std::find_if_not(vec.begin(), vec.end(), isEven); it != v.end())
    {
        std::cout << "odd number: " << *it << std::endl;
    }

    return 0;
}

#include <iostream>
#include <string>
#include <utility>

/**
 * Struct binding
 */

int main()
{
    std::pair<int, std::string> const intPair{1, "test"};
    auto [number, name] = intPair;
    std::cout << "Number:" << number << "Name:" << name << "\n";
    return 0;
}

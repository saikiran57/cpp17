#include <iostream>

/**
 * Struct binding
 */

int main()
{
    std::pair<int, std::string> intPair{1, "test"};
    auto [number, name] = intPair;
    std::cout << "Number:" << number << "Name:" << name << "\n";
    return 0;
}

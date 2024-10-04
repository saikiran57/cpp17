#include <iomanip>  // std::setfill, std::setw
#include <iostream>

int main()
{
    // setfill is x and width is set as 10
    std::cout << std::setfill('x') << std::setw(10);

    std::cout << 77 << std::endl;

    std::string str = "s";

    // setfill is G and width is set as 10
    // And std::left is used set str to left side
    std::cout << std::left << std::setfill('G') << std::setw(6);

    std::cout << str << std::endl;

    return 0;
}
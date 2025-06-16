/**
 * @file split_byte_string.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-06-12
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bitset>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include <iomanip>

using ByteArray = std::vector<std::byte>;

std::ostream& operator<<(std::ostream& os, std::byte b)
{
    return os << std::bitset<8>(std::to_integer<int>(b));
}

void print(ByteArray& bytes)
{
    std::cout << "{ " << std::hex << std::uppercase << std::setfill('0');
    for (auto const b : bytes)
        std::cout << std::setw(2) << std::to_integer<int>(b) << ' ';
    std::cout << std::dec << "}\n";
}

template <typename T>
void toByteArray(ByteArray& byteArray, const T& value)
{
    size_t size = sizeof(T);
    std::memcpy(byteArray.data(), &value, size);
}

ByteArray split_string()
{
    ByteArray byteArray(256);

    int i = 1000;
    double d = 12.222;
    std::string s = "my string";

    toByteArray(byteArray, i);
    toByteArray(byteArray, d);
    toByteArray(byteArray, s);
    print(byteArray);
    // for (auto ch : byteArray)
    // {
    //     std::cout << ch;
    // }

    return byteArray;
}

int main(int argc, char const* argv[])
{
    auto data = split_string();
    return 0;
}

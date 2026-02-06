#include "byte_array.hpp"
#include <cstdint>
#include <ios>
#include <iostream>
#include <ostream>
#include <vector>

using namespace experiment;

static void print(std::vector<uint8_t> data)
{
    for (auto byte : data)
    {
        std::cout << std::hex << static_cast<int>(byte) << ' ';
    }
    std::cout << std::dec << std::endl;
}

int main()
{
    std::vector<uint8_t> const data{0x2a, 0xff, 0x30};
    ByteArray ba(data);

    ba.append(data);

    std::cout << "address:" << ba.to_string() << "\n";

    ByteArray const b1("aabbccdd");

    std::cout << "address:" << b1.to_string() << "\n";

    print(ba.data());
}
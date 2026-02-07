#include <climits>  // For CHAR_BIT
#include <cstdint>
#include <iostream>

template <typename T>
static int countTrailingZeros(T num)
{
    if (num == 0)
    {
        return sizeof(num) * CHAR_BIT;  // All bits are zero
    }

    int count = 0;

    // Loop until the least significant bit is 1 or num becomes 0
    while ((num & 1) == 0 && num != 0)
    {
        count++;
        num >>= 1;  // Right shift to check the next bit
    }

    return count;
}

int main()
{
    uint8_t const num = 0;  // Example number
    std::cout << "Number of trailing zeros in " << num << " is: " << countTrailingZeros(num) << std::endl;
    return 0;
}

/**
 * @file bitset.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2025-04-09
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bitset>
#include <cstddef>
#include <iostream>

bool digitLimit(long long number, int limit, std::string& s)
{
    // check suffix
    auto nstr = std::to_string(number);

    if (nstr.substr(nstr.length() - s.length()) == s)
    {
        while (number)
        {
            auto digit = number % 10;

            if (digit > limit)
            {
                return false;
            }

            number = number / 10;
        }
    }
    else
    {
        return false;
    }

    return true;
}

long long numberOfPowerfulInt(long long start, long long finish, int limit, std::string s)
{
    auto snum = std::stol(s);

    if (finish < snum || (finish < start + snum))
    {
        return 0;
    }

    long long count = 0;

    long long i = start > snum ? start : snum;

    for (; i <= finish; ++i)
    {
        if (digitLimit(i, limit, s))
        {
            std::cout << i << std::endl;
            ++count;
        }
    }

    return count;
}

int main()
{
    std::bitset<8> b;
    std::cout << b << '\n';
    std::cout << b.set(1) << '\n';
    std::cout << b.reset() << '\n';

    for (std::size_t i = 1; i < b.size(); i += 2)
        b.set(i);

    std::bitset<8> sufix(124);  // 01111100

    int limit = 4;
    int level = 1;

    auto count = numberOfPowerfulInt(1, 6000, 4, "124");
    std::cout << "count: " << count << "\n";

    count = numberOfPowerfulInt(15, 215, 6, "10");
    std::cout << "count: " << count << "\n";

    count = numberOfPowerfulInt(1, 971, 9, "71");
    std::cout << "count: " << count << "\n";

    // for(int i = 1; i < 10000; ++i)
    // {
    //     if (digitLimit(i, limit))
    //     {
    //         std::cout << i << '\n';
    //     }

    // }

    std::cout << sufix << '\n';
}
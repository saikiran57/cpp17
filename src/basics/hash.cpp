/**
 * @file hash.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2025-01-28
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>

/**
 * @brief https://cp-algorithms.com/string/string-hashing.html
 *
 * @param s
 * @return long long
 */
static size_t compute_hash(std::string const& s)
{
    const int p = 31;
    const int m = 1e9 + 9;
    size_t hash_value = 0;
    size_t p_pow = 1;
    for (char const c : s)
    {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}

struct MyStringHash
{
    std::size_t operator()(const std::string& str) const noexcept
    {
        size_t hash = 0;

        for (auto&& i : str)
        {
            hash += i - 'a';
        }

        // hash = std::hash<std::string>{}(str);
        hash = compute_hash(str);
        std::cout << "Hashed value for " << str << " value: " << hash << "\n";
        return hash;
    }
};

int main()
{
    // std::string str = "sai";
    // std::size_t str_hash = MyStringHash{}(str);
    // std::cout << "hash(" << std::quoted(str) << ") =\t" << str_hash << '\n';

    // str = "iasi";
    // str_hash = MyStringHash{}(str);
    // std::cout << "hash(" << std::quoted(str) << ") =\t" << str_hash << '\n';

    std::unordered_map<std::string, std::string, MyStringHash> uMap;

    std::string const str = "sai";
    uMap[str] = str;
    const auto* str2 = "ias";
    uMap[str2] = str2;

    std::cout << "uMpa size: " << uMap.size() << "\n";

    return 0;
}
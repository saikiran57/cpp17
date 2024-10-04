/**
 * @file byte_array.hpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2024-08-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

namespace experiment
{

/**
 * @brief To store byte information
 *
 */
class ByteArray
{
public:
    /**
     * @brief Construct a new Byte Array object
     *
     */
    ByteArray() = default;

    /**
     * @brief Construct a new Byte Array object from uint8_t
     *
     * @param data
     * @param size
     */
    ByteArray(const uint8_t* data, std::size_t size) : m_ByteArray(data, data + size) {}

    /**
     * @brief Construct a new Byte Array object from vector of uint8_t
     *
     * @param byteArray
     */
    ByteArray(const std::vector<uint8_t>& byteArray) : m_ByteArray(byteArray) {}

    ByteArray(const std::string& hexString)
    {
        load_from_hex(hexString);
    }

    /**
     * @brief Method for loading bytearray data from hex.
     * If bytearray already contains any data - it will be erased.
     * @param s Hex string. Example: "aabbccdd" or "AABBDDCC" or "AA BB CC DD"
     * @return Success. If fail - previous data will not be erased.
     */
    bool load_from_hex(const std::string& s)
    {
        return load_from_hex(std::string_view(s));
    }

    /**
     * @brief Method for loading bytearray data from hex.
     * If bytearray already contains any data - it will be erased.
     * @param sv Hex string view. Example: "aabbccdd" or "AABBDDCC" or "AA BB CC DD"
     * @return Success. If fail - previous data will not be erased.
     */
    bool load_from_hex(const std::string_view& sv)
    {
        static auto validator = [](char c) {
            return (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') || (c >= '0' && c <= '9');
        };

        static auto char2int = [](char symbol) -> uint8_t {
            if (symbol >= '0' && symbol <= '9')
            {
                return static_cast<uint8_t>(symbol - '0');
            }
            else if (symbol >= 'A' && symbol <= 'F')
            {
                return static_cast<uint8_t>(symbol - 'A' + 10);
            }
            else if (symbol >= 'a' && symbol <= 'f')
            {
                return static_cast<uint8_t>(symbol - 'a' + 10);
            }

            throw std::runtime_error("Received unknown symbol");
        };

        // Checking string
        auto found = std::find_if(sv.begin(), sv.end(), [](char c) {
            return (c < 'a' || c > 'f') && (c < 'A' || c > 'F') && (c < '0' || c > '9') && (c != ' ');
        });

        if (found != sv.end())
        {
            return false;
        }

        // Parsing
        auto count = std::count_if(sv.begin(), sv.end(), validator);

        m_ByteArray.clear();
        m_ByteArray.reserve(count);

        bool isFirst = true;
        uint8_t firstValue = 0;

        for (auto symbol : sv)
        {
            if (!validator(symbol))
            {
                continue;
            }

            if (isFirst)
            {
                firstValue = char2int(symbol);

                isFirst = false;
            }
            else
            {
                m_ByteArray.push_back(std::uint8_t(firstValue * 16 + char2int(symbol)));

                isFirst = true;
            }
        }

        return true;
    }

    /**
     * @brief Destroy the Byte Array object
     *
     */
    ~ByteArray() = default;

    ByteArray(const ByteArray& other) = default;
    ByteArray& operator=(const ByteArray& other) = default;
    ByteArray(ByteArray&& other) = default;
    ByteArray& operator=(ByteArray&& other) = default;

    /**
     * @brief append two byte arrays
     *
     * @param other
     * @return ByteArray&
     */
    ByteArray& operator+(const ByteArray& other) noexcept
    {
        auto otherData = other.data();
        m_ByteArray.insert(m_ByteArray.begin(), otherData.begin(), otherData.end());
        return *this;
    }

    ByteArray& append(const std::vector<uint8_t>& data) noexcept
    {
        m_ByteArray.insert(m_ByteArray.begin(), data.begin(), data.end());
        return *this;
    }

    /**
     * @brief return internal data of ByteArray
     *
     * @return std::vector<uint8_t>
     */
    [[nodiscard]] std::vector<uint8_t> data() const noexcept
    {
        return m_ByteArray;
    }

    [[nodiscard]] size_t size() const noexcept
    {
        return m_ByteArray.size();
    }

    std::string to_string(bool upperCase=true, bool prefix=true) const noexcept
    {
        std::stringstream ss;

        ss << (upperCase ? std::uppercase : std::nouppercase) << (prefix ? "0x": "" );

        for (auto&& byte : m_ByteArray)
        {
            ss << (upperCase ? std::uppercase : std::nouppercase) << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(byte);
        }

        return ss.str();
    }

private:
    std::vector<uint8_t> m_ByteArray;  ///< internal ByteArray representation
};
}  // namespace experiment
/**
 * @file map_with_high_load.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2025-01-16
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "execution_timer.hpp"
#include <array>
#include <chrono>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <unordered_map>

// Class to represent a 256-bit unsigned integer
class uint256
{
public:
    std::array<uint8_t, 32> data{};  // 256 bits = 32 bytes

    uint256()
    {
        data.fill(0);
    }

    uint256(const std::array<uint8_t, 32>& arr) : data(arr) {}

    bool operator<(const uint256& other) const
    {
        return data < other.data;
    }

    bool operator==(const uint256& other) const
    {
        return data == other.data;
    }

    struct Hash
    {
        std::size_t operator()(const uint256& key) const
        {
            std::size_t hash = 0;
            for (const auto& byte : key.data)
            {
                hash = (hash * 31) ^ byte;
            }
            return hash;
        }
    };

    friend std::ostream& operator<<(std::ostream& os, const uint256& val)
    {
        for (const auto& byte : val.data)
        {
            os << std::hex << static_cast<int>(byte);
        }
        return os;
    }
};

// Function to generate a random uint256 value
uint256 generateRandomUint256(std::mt19937& rng)
{
    std::array<uint8_t, 32> randomData;
    std::uniform_int_distribution<uint16_t> dist(0, 255);

    for (auto& byte : randomData)
    {
        byte = static_cast<uint8_t>(dist(rng));
    }
    return uint256(randomData);
}

class ScriptPubKeyMan
{
public:
    ScriptPubKeyMan() = default;
    virtual ~ScriptPubKeyMan() = default;
};

class DescriptorScriptPubKeyMan : public ScriptPubKeyMan
{
    std::string descriptor;

public:
    DescriptorScriptPubKeyMan(const std::string& desc) : descriptor(desc) {}
    ~DescriptorScriptPubKeyMan() = default;
    bool HasWalletDescriptor(const std::string& desc) const
    {
        return descriptor == desc;
    }
};

using AddressMap = std::unordered_map<uint256, std::unique_ptr<ScriptPubKeyMan>, uint256::Hash>;
// using AddressMap = std::map<uint256, std::unique_ptr<ScriptPubKeyMan>>;

bool hasAddress(const std::string& myrandomAddress, AddressMap& addressMap)
{
    for (auto& address : addressMap)
    {
        //++i;
        // Try to downcast to DescriptorScriptPubKeyMan then check if the descriptors match
        DescriptorScriptPubKeyMan* spk_manager = dynamic_cast<DescriptorScriptPubKeyMan*>(address.second.get());
        if (spk_manager != nullptr && spk_manager->HasWalletDescriptor(myrandomAddress))
        {
            // std::cout << "found: " << myrandomAddress << " count " << std::to_string(i) << " first " << address.first
            //           << "\n";
            return true;
        }

        // std::cout << " count "<<  std::to_string(i) << "\n";
    }

    return false;
}

int main()
{
    const size_t addressCount = 2000000;
    // AddressMap addressMap;
    AddressMap addressMap;
    std::string myrandomAddress;

    // Initialize random number generator
    std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());

    {
        ExecutionTimer<std::chrono::seconds> et;

        // Generate 2 million random addresses
        for (size_t i = 0; i < addressCount; ++i)
        {
            uint256 randomAddress = generateRandomUint256(rng);
            auto descriptor = "Address" + std::to_string(i);
            addressMap[randomAddress] = std::make_unique<DescriptorScriptPubKeyMan>(descriptor);
        }
    }

    {
        ExecutionTimer<std::chrono::seconds> et;
        auto iteration = 0;
        while (iteration < 1000)
        {
            // ExecutionTimer<std::chrono::milliseconds> et;

            size_t i = 0;
            std::uniform_int_distribution<size_t> dist(0, addressCount);

            myrandomAddress = "Address" + std::to_string(dist(rng));

            ++iteration;

            std::cout << "iteration: " << iteration << " address: " << myrandomAddress
                      << " found: " << hasAddress(myrandomAddress, addressMap) << "\n";

            // Generate a random address to search
            // uint256 searchAddress = generateRandomUint256(rng);

            // Search for the random address in the ma
            // auto it = addressMap.find(myrandomAddress);
            // if (it != addressMap.end())
            // {
            //     std::cout << "Found address: " << it->second << " with key: " << it->first << "\n";
            // }
            // else
            // {
            //     std::cout << "Address not found." << std::endl;
            // }
        }
    }

    return 0;
}

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
#include <mutex>
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
    bool HasWalletDescriptor(const std::string& desc) const;
};

class DescriptorScriptPubKeyMan : public ScriptPubKeyMan
{
    std::string descriptor;
    mutable std::recursive_mutex cs_desc_man;

public:
    DescriptorScriptPubKeyMan(const std::string& desc) : descriptor(desc) {}
    ~DescriptorScriptPubKeyMan() = default;
    bool HasWalletDescriptor(const std::string& desc) const
    {
        std::scoped_lock lk(cs_desc_man);
        return descriptor == desc;
    }
};

// using AddressMap = std::unordered_map<uint256, std::unique_ptr<ScriptPubKeyMan>, uint256::Hash>;
using AddressMap = std::map<uint256, std::unique_ptr<ScriptPubKeyMan>>;

class CWallet final
{
public:
    explicit CWallet(const size_t addressCount = 2000000);
    bool AddWalletDescriptor_Old(const uint256& index, const std::string& address);
    bool AddWalletDescriptor_New(const uint256& index, const std::string& address);
    void AddScriptPubKeyMan(const uint256& id, std::unique_ptr<ScriptPubKeyMan> spkm_man);
    DescriptorScriptPubKeyMan* GetDescriptorScriptPubKeyMan_New(const uint256& index,
                                                                const std::string& myrandomAddress) const;
    DescriptorScriptPubKeyMan* GetDescriptorScriptPubKeyMan_Old(const std::string& myrandomAddress) const;

private:
    // Indexed by a unique identifier produced by each ScriptPubKeyMan using
    // ScriptPubKeyMan::GetID. In many cases it will be the hash of an internal structure
    AddressMap m_spk_managers;
};

CWallet::CWallet(const size_t addressCount)
{
    // std::string myrandomAddress;
    // std::uniform_int_distribution<size_t> dist(0, addressCount);

    // Initialize random number generator
    std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
    {
        auto message = "Load wallet with given size:" + std::to_string(addressCount);
        ExecutionTimer<std::chrono::seconds> et(message);

        // Generate 2 million random addresses
        for (size_t i = 0; i < addressCount; ++i)
        {
            uint256 randomAddress = generateRandomUint256(rng);
            auto descriptor = "Address" + std::to_string(i);
            m_spk_managers[randomAddress] = std::make_unique<DescriptorScriptPubKeyMan>(descriptor);
        }
    }
}

bool CWallet::AddWalletDescriptor_Old(const uint256& index, const std::string& address)
{
    auto spk_mgr = GetDescriptorScriptPubKeyMan_Old(address);

    if (spk_mgr)
    {
        return true;
    }
    else
    {
        auto new_spk_man = std::make_unique<DescriptorScriptPubKeyMan>(address);
        AddScriptPubKeyMan(index, std::move(new_spk_man));
    }
    return false;
}

DescriptorScriptPubKeyMan* CWallet::GetDescriptorScriptPubKeyMan_Old(const std::string& myrandomAddress) const
{
    for (auto& spk_man_pair : m_spk_managers)
    {
        // Try to downcast to DescriptorScriptPubKeyMan then check if the descriptors match
        DescriptorScriptPubKeyMan* spk_manager = dynamic_cast<DescriptorScriptPubKeyMan*>(spk_man_pair.second.get());
        if (spk_manager != nullptr && spk_manager->HasWalletDescriptor(myrandomAddress))
        {
            return spk_manager;
        }
    }

    return nullptr;
}

bool CWallet::AddWalletDescriptor_New(const uint256& index, const std::string& address)
{
    auto spk_mgr = GetDescriptorScriptPubKeyMan_New(index, address);

    if (spk_mgr)
    {
        return true;
    }
    else
    {
        auto new_spk_man = std::make_unique<DescriptorScriptPubKeyMan>(address);
        AddScriptPubKeyMan(index, std::move(new_spk_man));
    }
    return false;
}

DescriptorScriptPubKeyMan* CWallet::GetDescriptorScriptPubKeyMan_New(const uint256& index,
                                                                     const std::string& myrandomAddress) const
{
    auto spk_man_pair = m_spk_managers.find(index);

    if (spk_man_pair != m_spk_managers.end())
    {
        DescriptorScriptPubKeyMan* spk_manager = dynamic_cast<DescriptorScriptPubKeyMan*>(spk_man_pair->second.get());
        if (spk_manager != nullptr && spk_manager->HasWalletDescriptor(myrandomAddress))
        {
            return spk_manager;
        }
    }

    return nullptr;
}

void CWallet::AddScriptPubKeyMan(const uint256& id, std::unique_ptr<ScriptPubKeyMan> spkm_man)
{
    // Add spkm_man to m_spk_managers before calling any method
    // that might access it.
    m_spk_managers[id] = std::move(spkm_man);
}

int main()
{
    const size_t addressCount = 2000000;

    CWallet wallet(addressCount);
    // driver code to test 1000
    auto iterationCount = 100;

    {
        // Test existing descriptor
        ExecutionTimer<std::chrono::seconds> et("Importdescriptor call with old code");
        auto iteration = 0;
        size_t i = addressCount;
        std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
        while (iteration < iterationCount)
        {
            ExecutionTimer<std::chrono::milliseconds> et;
            auto myrandomAddress = "Address" + std::to_string(i);
            uint256 index = generateRandomUint256(rng);

            // Check if the wallet already contains the descriptor
            auto existing_spk_manager = wallet.GetDescriptorScriptPubKeyMan_Old(myrandomAddress);
            if (existing_spk_manager)
            {
                break;
            }

            std::cout << "iteration: " << iteration << " address: " << myrandomAddress
                      << " found: " << wallet.AddWalletDescriptor_Old(index, myrandomAddress) << "\n";
            ++iteration;
            ++i;
        }
    }

    std::cout << "--------------- test case new code ----------------\n";
    {
        // Test improved descriptor
        ExecutionTimer<std::chrono::seconds> et("Importdescriptor call with new code");
        auto iteration = 0;
        size_t i = addressCount;
        std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
        while (iteration < iterationCount)
        {
            ExecutionTimer<std::chrono::milliseconds> et;
            auto myrandomAddress = "Address" + std::to_string(i);
            uint256 index = generateRandomUint256(rng);

            std::cout << "iteration: " << iteration << " address: " << myrandomAddress
                      << " found: " << wallet.AddWalletDescriptor_New(index, myrandomAddress) << "\n";
            ++iteration;
            ++i;
        }
    }
}
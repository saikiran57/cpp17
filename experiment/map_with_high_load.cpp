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
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <random>
#include <string>
#include <utility>

// Class to represent a 256-bit unsigned integer
class Uint256
{
public:
    std::array<uint8_t, 32> m_data{};  // 256 bits = 32 bytes

    Uint256()
    {
        m_data.fill(0);
    }

    explicit Uint256(const std::array<uint8_t, 32>& arr) : m_data(arr) {}

    bool operator<(const Uint256& other) const
    {
        return m_data < other.m_data;
    }

    bool operator==(const Uint256& other) const
    {
        return m_data == other.m_data;
    }

    struct Hash
    {
        std::size_t operator()(const Uint256& key) const
        {
            std::size_t hash = 0;
            for (const auto& byte : key.m_data)
            {
                hash = (hash * 31) ^ byte;
            }
            return hash;
        }
    };

    friend std::ostream& operator<<(std::ostream& os, const Uint256& val)
    {
        for (const auto& byte : val.m_data)
        {
            os << std::hex << static_cast<int>(byte);
        }
        return os;
    }
};

// Function to generate a random uint256 value
static Uint256 generateRandomUint256(std::mt19937& rng)
{
    std::array<uint8_t, 32> randomData{};
    std::uniform_int_distribution<uint16_t> dist(0, 255);

    for (auto& byte : randomData)
    {
        byte = static_cast<uint8_t>(dist(rng));
    }
    return Uint256(randomData);
}

class ScriptPubKeyMan
{
public:
    ScriptPubKeyMan() = default;
    virtual ~ScriptPubKeyMan() = default;
    [[nodiscard]] bool hasWalletDescriptor(const std::string& desc) const;
};

class DescriptorScriptPubKeyMan : public ScriptPubKeyMan
{
    std::string m_descriptor;
    mutable std::recursive_mutex m_csDescMan;

public:
    explicit DescriptorScriptPubKeyMan(std::string desc) : m_descriptor(std::move(desc)) {}
    ~DescriptorScriptPubKeyMan() override = default;
    bool hasWalletDescriptor(const std::string& desc) const
    {
        std::scoped_lock const lk(m_csDescMan);
        return m_descriptor == desc;
    }
};

// using AddressMap = std::unordered_map<uint256, std::unique_ptr<ScriptPubKeyMan>, uint256::Hash>;
using t_AddressMap = std::map<Uint256, std::unique_ptr<ScriptPubKeyMan>>;

class CWallet final
{
public:
    explicit CWallet(size_t addressCount = 2000000);
    bool addWalletDescriptorOld(const Uint256& index, const std::string& address);
    bool addWalletDescriptorNew(const Uint256& index, const std::string& address);
    void addScriptPubKeyMan(const Uint256& id, std::unique_ptr<ScriptPubKeyMan> spkm_man);
    [[nodiscard]] DescriptorScriptPubKeyMan* getDescriptorScriptPubKeyManNew(const Uint256& index,
                                                                             const std::string& myrandomAddress) const;
    [[nodiscard]] DescriptorScriptPubKeyMan* getDescriptorScriptPubKeyManOld(const std::string& myrandomAddress) const;

private:
    // Indexed by a unique identifier produced by each ScriptPubKeyMan using
    // ScriptPubKeyMan::GetID. In many cases it will be the hash of an internal structure
    t_AddressMap m_mSpkManagers;
};

CWallet::CWallet(const size_t addressCount)
{
    // std::string myrandomAddress;
    // std::uniform_int_distribution<size_t> dist(0, addressCount);

    // Initialize random number generator
    std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
    {
        auto message = "Load wallet with given size:" + std::to_string(addressCount);
        ExecutionTimer<std::chrono::seconds> const et(message);

        // Generate 2 million random addresses
        for (size_t i = 0; i < addressCount; ++i)
        {
            Uint256 const randomAddress = generateRandomUint256(rng);
            auto descriptor = "Address" + std::to_string(i);
            m_mSpkManagers[randomAddress] = std::make_unique<DescriptorScriptPubKeyMan>(descriptor);
        }
    }
}

bool CWallet::addWalletDescriptorOld(const Uint256& index, const std::string& address)
{
    auto* spk_mgr = getDescriptorScriptPubKeyManOld(address);

    if (spk_mgr != nullptr)
    {
        return true;
    }
    else
    {
        auto new_spk_man = std::make_unique<DescriptorScriptPubKeyMan>(address);
        addScriptPubKeyMan(index, std::move(new_spk_man));
    }
    return false;
}

DescriptorScriptPubKeyMan* CWallet::getDescriptorScriptPubKeyManOld(const std::string& myrandomAddress) const
{
    for (const auto& spk_man_pair : m_mSpkManagers)
    {
        // Try to downcast to DescriptorScriptPubKeyMan then check if the descriptors match
        auto const* spk_manager = dynamic_cast<DescriptorScriptPubKeyMan*>(spk_man_pair.second.get());
        if (spk_manager != nullptr && spk_manager->hasWalletDescriptor(myrandomAddress))
        {
            return spk_manager;
        }
    }

    return nullptr;
}

bool CWallet::addWalletDescriptorNew(const Uint256& index, const std::string& address)
{
    auto* spk_mgr = getDescriptorScriptPubKeyManNew(index, address);

    if (spk_mgr != nullptr)
    {
        return true;
    }
    else
    {
        auto new_spk_man = std::make_unique<DescriptorScriptPubKeyMan>(address);
        addScriptPubKeyMan(index, std::move(new_spk_man));
    }
    return false;
}

DescriptorScriptPubKeyMan* CWallet::getDescriptorScriptPubKeyManNew(const Uint256& index,
                                                                    const std::string& myrandomAddress) const
{
    auto spk_man_pair = m_mSpkManagers.find(index);

    if (spk_man_pair != m_mSpkManagers.end())
    {
        auto const* spk_manager = dynamic_cast<DescriptorScriptPubKeyMan*>(spk_man_pair->second.get());
        if (spk_manager != nullptr && spk_manager->hasWalletDescriptor(myrandomAddress))
        {
            return spk_manager;
        }
    }

    return nullptr;
}

void CWallet::addScriptPubKeyMan(const Uint256& id, std::unique_ptr<ScriptPubKeyMan> spkm_man)
{
    // Add spkm_man to m_spk_managers before calling any method
    // that might access it.
    m_mSpkManagers[id] = std::move(spkm_man);
}

int main()
{
    const size_t addressCount = 2000000;

    CWallet wallet(addressCount);
    // driver code to test 1000
    auto iterationCount = 100;

    {
        // Test existing descriptor
        ExecutionTimer<std::chrono::seconds> const et("Importdescriptor call with old code");
        auto iteration = 0;
        size_t i = addressCount;
        std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
        while (iteration < iterationCount)
        {
            ExecutionTimer<std::chrono::milliseconds> const et;
            auto myrandomAddress = "Address" + std::to_string(i);
            Uint256 const index = generateRandomUint256(rng);

            // Check if the wallet already contains the descriptor
            auto* existing_spk_manager = wallet.getDescriptorScriptPubKeyManOld(myrandomAddress);
            if (existing_spk_manager != nullptr)
            {
                break;
            }

            std::cout << "iteration: " << iteration << " address: " << myrandomAddress
                      << " found: " << wallet.addWalletDescriptorOld(index, myrandomAddress) << "\n";
            ++iteration;
            ++i;
        }
    }

    std::cout << "--------------- test case new code ----------------\n";
    {
        // Test improved descriptor
        ExecutionTimer<std::chrono::seconds> const et("Importdescriptor call with new code");
        auto iteration = 0;
        size_t i = addressCount;
        std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
        while (iteration < iterationCount)
        {
            ExecutionTimer<std::chrono::milliseconds> const et;
            auto myrandomAddress = "Address" + std::to_string(i);
            Uint256 const index = generateRandomUint256(rng);

            std::cout << "iteration: " << iteration << " address: " << myrandomAddress
                      << " found: " << wallet.addWalletDescriptorNew(index, myrandomAddress) << "\n";
            ++iteration;
            ++i;
        }
    }
}
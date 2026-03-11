/**
 * @file circular_dependency.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-02-24
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Team;

struct PlayerInfo
{
    std::uint64_t m_id;
    std::string m_name;
};

class Player
{
public:
    Player()
    {
        std::cout << "Player constructed \n";
    }
    ~Player()
    {
        std::cout << "Player destructed " << m_info.m_id << "\n";
    }
    Player(PlayerInfo info) : m_info(std::move(info))
    {
        std::cout << "Player constructed: " << m_info.m_id << "\n";
    }

    std::shared_ptr<Player> getPartner() const noexcept
    {
        return m_partner.lock();
    }

    friend void partnership(std::shared_ptr<Player>& p1, std::shared_ptr<Player>& p2);

    friend Team;

private:
    PlayerInfo m_info;
    std::weak_ptr<Player> m_partner;  // To avoid circular dependency issue we must use weak_ptr
};

void partnership(std::shared_ptr<Player>& p1, std::shared_ptr<Player>& p2)
{
    if (p1 != p2)
    {
        p1->m_partner = p2;
        p2->m_partner = p1;
    }
}

class Team
{
public:
    void partnership(std::shared_ptr<Player>& p1, std::shared_ptr<Player>& p2)
    {
        if (p1 != p2)
        {
            // Actually set the partnership in the Player objects
            p1->m_partner = p2;
            p2->m_partner = p1;

            m_partnership.push_back(std::make_pair(p1, p2));
        }
    }

    void display() const noexcept
    {
        for (const auto& [p1, p2] : m_partnership)
        {
            auto p1_ = p1.lock();
            auto p2_ = p2.lock();

            if (p1_ && p2_)
            {
                std::cout << "Partnership: Player " << p1_->m_info.m_id << " (" << p1_->m_info.m_name
                          << ") with Player " << p2_->m_info.m_id << " (" << p2_->m_info.m_name << ")\n";

                // Verify the partner link works
                if (auto partner = p1_->m_partner.lock())
                {
                    std::cout << "  Verified: " << p1_->m_info.m_name << "'s partner is " << partner->m_info.m_name
                              << "\n";
                }
            }
        }
    }

    // Optional: Add method to remove expired partnerships
    void cleanup()
    {
        m_partnership.erase(std::remove_if(m_partnership.begin(), m_partnership.end(),
                                           [](const auto& pair) {
                                               return pair.first.expired() || pair.second.expired();
                                           }),
                            m_partnership.end());
    }

private:
    std::vector<std::pair<std::weak_ptr<Player>, std::weak_ptr<Player>>> m_partnership;
};

int main()
{
    // without team
    // {
    //     std::shared_ptr<Player> p1 = std::make_shared<Player>();
    //     std::shared_ptr<Player> p2 = std::make_shared<Player>();

    //     partnership(p1, p2);

    //     std::shared_ptr<Player> p3 = std::make_shared<Player>();
    //     std::shared_ptr<Player> p4 = std::make_shared<Player>();

    //     partnership(p3, p4);
    // }

    // with team
    {
        PlayerInfo p1Info{1, "Alice"};
        PlayerInfo p2Info{2, "Bob"};
        PlayerInfo p3Info{3, "Charlie"};
        PlayerInfo p4Info{4, "David"};
        PlayerInfo p5Info{5, "Eve"};

        Team team;

        auto p1 = std::make_shared<Player>(p1Info);
        auto p2 = std::make_shared<Player>(p2Info);
        auto p3 = std::make_shared<Player>(p3Info);
        auto p4 = std::make_shared<Player>(p4Info);

        team.partnership(p1, p2);
        team.partnership(p3, p4);

        std::cout << "\nInitial partnerships:\n";
        team.display();

        // Replace player 3 with player 5
        std::cout << "\n=== Player 3 replaced with Player 5 ===\n";
        p3.reset();  // Player 3 destroyed

        // Clean up expired partnerships before adding new ones
        team.cleanup();

        auto p5 = std::make_shared<Player>(p5Info);
        team.partnership(p5, p4);

        std::cout << "\nUpdated partnerships:\n";
        team.display();

        // Reset player 5
        std::cout << "\n=== Player 5 rested ===\n";
        p5.reset();  // Player 3 destroyed

        std::cout << "\n display updated:\n";
        team.display();

        // Cleanup at the end
        team.cleanup();
    }
}
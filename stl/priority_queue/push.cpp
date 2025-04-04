#include <iostream>
#include <queue>
#include <string>
#include <utility>

struct Event
{
    int m_priority;
    std::string m_data;

    Event(int p, std::string d) : m_priority(p), m_data(std::move(d)) {}

    /**
     * @brief comparison between two events
     *
     * @param lhs
     * @param rhs
     * @return true
     * @return false
     */
    friend constexpr bool operator<(const Event& lhs, const Event& rhs) noexcept
    {
        return lhs.m_priority < rhs.m_priority;
    }

    friend std::ostream& operator<<(std::ostream& os, const Event& event) noexcept
    {
        return os << "priority:" << event.m_priority << " data:" << event.m_data << "\n";
    }
};

int main()
{
    using namespace std::string_literals;
    std::priority_queue<Event> pqEvents;
    std::string const temp = "sdsdsdsdsds";
    pqEvents.emplace(1, "ssdsd");
    pqEvents.emplace(23, temp);

    while (!pqEvents.empty())
    {
        std::cout << pqEvents.top();
        pqEvents.pop();
    }

    return 0;
}
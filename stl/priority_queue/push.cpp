#include <iostream>
#include <queue>
#include <string>

struct Event
{
    int priority;
    std::string data;

    Event(int p, const std::string& d) : priority(p), data(d) {}

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
        return lhs.priority < rhs.priority;
    }

    friend std::ostream& operator<<(std::ostream& os, const Event& event) noexcept
    {
        return os << "priority:" << event.priority << " data:" << event.data << "\n";
    }
};

int main()
{
    using namespace std::string_literals;
    std::priority_queue<Event> pqEvents;
    std::string temp = "sdsdsdsdsds";
    pqEvents.push(Event{1, "ssdsd"});
    pqEvents.emplace(23, temp);

    while (!pqEvents.empty())
    {
        std::cout << pqEvents.top();
        pqEvents.pop();
    }

    return 0;
}
/**
 * @file source_listner.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-02-23
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

enum class EventType
{
    BOOKED,
    RESERVED,
    CANCELLED
};

struct Event
{
    std::uint64_t id;
    std::string message;
    EventType eventType = EventType::BOOKED;
};

class IListener
{
public:
    virtual ~IListener() = default;
    virtual void onEvent(const Event& event) noexcept = 0;
};

class Listener : public IListener
{
public:
    explicit Listener(std::uint64_t id) : id(id) {}  // Use initializer list

    ~Listener() override
    {
        std::cout << "Listener destructor for ID: " << id << "\n";
    }

    void onEvent(const Event& event) noexcept override
    {
        std::cout << "Listener Id: " << this->id << " Event Id: " << event.id << " message: " << event.message << "\n";
    }

private:
    std::uint64_t id;
};

class Source
{
public:
    void dispatch_event(const Event& event) noexcept
    {
        // Use traditional loop to safely remove expired listeners
        for (auto it = m_Listeners.begin(); it != m_Listeners.end();)
        {
            if (auto listener = it->lock())
            {
                listener->onEvent(event);
                ++it;
            }
            else
            {
                it = m_Listeners.erase(it);  // erase returns next iterator
            }
        }
    }

    void register_listener(std::weak_ptr<IListener> listener) noexcept
    {
        m_Listeners.push_back(listener);
    }

    // Optional: Add method to clean up expired listeners
    void cleanup_expired_listeners() noexcept
    {
        m_Listeners.erase(std::remove_if(m_Listeners.begin(), m_Listeners.end(),
                                         [](const auto& weak_ptr) {
                                             return weak_ptr.expired();
                                         }),
                          m_Listeners.end());
    }

private:
    std::vector<std::weak_ptr<IListener>> m_Listeners;
};

int main()
{
    Source source;

    auto listener1 = std::make_shared<Listener>(111);
    source.register_listener(listener1);

    {
        auto listener2 = std::make_shared<Listener>(222);
        source.register_listener(listener2);
    }  // listener2 is destroyed here

    Event event{1, "test1"};
    source.dispatch_event(event);

    auto listener3 = std::make_shared<Listener>(333);
    source.register_listener(listener3);

    Event event2{2, "test2"};
    source.dispatch_event(event2);

    return 0;
}
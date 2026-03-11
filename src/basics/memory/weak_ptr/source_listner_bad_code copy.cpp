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

#include <cstdint>
#include <iostream>
#include <memory>
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
    Listener(std::uint64_t id)
    {
        this->id = id;
    }
    ~Listener()
    {
        std::cout << "Listener destructor \n";
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
        for (auto& listener : m_Listeners)
        {
            if (listener) listener->onEvent(event);
        }
    }

    void register_listener(IListener* listener)
    {
        m_Listeners.push_back(listener);
    }

private:
    std::vector<IListener*> m_Listeners;
};

int main()
{
    Source source;
    std::shared_ptr<IListener> listener1 = std::make_shared<Listener>(111);
    source.register_listener(listener1.get());
    {
        std::shared_ptr<IListener> listener2 = std::make_shared<Listener>(222);
        source.register_listener(listener2.get());
    }

    Event event{1, "test1"};

    source.dispatch_event(event);
}


/**
 * @file variant.cpp
 * @author Saikiran Nadipilli
 * @brief
 * @version 0.1
 * @date 2025-01-31
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <iostream>
#include <variant>

/**
 * @brief https://dev.to/heliobatimarqui/compile-time-type-id-with-templates-c-55c4
 *
 */

// Our events
class MouseEvent
{
public:
    static void doMouseEventStuff()
    {
        std::cout << "Doing MouseEvent stuff\n";
    }
};

class KeyboardEvent
{
public:
    static void doKeyboardEventStuff()
    {
        std::cout << "Doing KeyboardEvent stuff\n";
    }
};

class JoystickEvent
{
public:
    static void doJoystickEventStuff()
    {
        std::cout << "Doing JoystickEvent stuff\n";
    }
};

// Another event, not recognized by the engine
class NotAnEngineEvent
{
};

// Create a type to represent the events the engine can handle
using t_Event = std::variant<MouseEvent, KeyboardEvent, JoystickEvent>;

// To use with std::visit (see below)
struct EventHandler
{
    void operator()(const MouseEvent& e)
    {
        MouseEvent::doMouseEventStuff();
    }

    void operator()(const KeyboardEvent& e)
    {
        KeyboardEvent::doKeyboardEventStuff();
    }

    void operator()(const JoystickEvent& e)
    {
        JoystickEvent::doJoystickEventStuff();
    }
};

int main()
{
    // Create events
    t_Event m = MouseEvent{};
    t_Event k = KeyboardEvent{};
    t_Event j = JoystickEvent{};

    // Test the type of the event manually
    if (std::holds_alternative<MouseEvent>(m))
    {
        auto e = std::get<MouseEvent>(m);
        MouseEvent::doMouseEventStuff();
    }

    if (auto* p = std::get_if<KeyboardEvent>(&k))
    {
        KeyboardEvent::doKeyboardEventStuff();
    }

    // With std::visit
    EventHandler handler;

    std::visit(handler, m);
    std::visit(handler, k);
    std::visit(handler, j);

    // Event bad = NotAnEngineEvent{}; // don't compile
}

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
    void do_mouse_event_stuff() const
    {
        std::cout << "Doing MouseEvent stuff\n";
    }
};

class KeyboardEvent
{
public:
    void do_keyboard_event_stuff() const
    {
        std::cout << "Doing KeyboardEvent stuff\n";
    }
};

class JoystickEvent
{
public:
    void do_joystick_event_stuff() const
    {
        std::cout << "Doing JoystickEvent stuff\n";
    }
};

// Another event, not recognized by the engine
class NotAnEngineEvent
{
};

// Create a type to represent the events the engine can handle
using Event = std::variant<MouseEvent, KeyboardEvent, JoystickEvent>;

// To use with std::visit (see below)
struct EventHandler
{
    void operator()(const MouseEvent& e)
    {
        e.do_mouse_event_stuff();
    }

    void operator()(const KeyboardEvent& e)
    {
        e.do_keyboard_event_stuff();
    }

    void operator()(const JoystickEvent& e)
    {
        e.do_joystick_event_stuff();
    }
};

int main()
{
    // Create events
    Event m = MouseEvent{};
    Event k = KeyboardEvent{};
    Event j = JoystickEvent{};

    // Test the type of the event manually
    if (std::holds_alternative<MouseEvent>(m))
    {
        auto e = std::get<MouseEvent>(m);
        e.do_mouse_event_stuff();
    }

    if (auto p = std::get_if<KeyboardEvent>(&k))
    {
        p->do_keyboard_event_stuff();
    }

    // With std::visit
    EventHandler handler;

    std::visit(handler, m);
    std::visit(handler, k);
    std::visit(handler, j);

    // Event bad = NotAnEngineEvent{}; // don't compile
}
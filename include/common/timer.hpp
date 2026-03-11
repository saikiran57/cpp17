#pragma once

#include <atomic>
#include <chrono>
#include <concepts>
#include <format>  // C++20
#include <iostream>
#include <source_location>  // C++20
#include <string>
#include <string_view>
#include <type_traits>

// Use concepts for better type checking (C++20)
template <typename T>
concept ChronoDuration = requires {
    typename T::rep;
    typename T::period;
    requires std::derived_from<T, std::chrono::duration<typename T::rep, typename T::period>>;
};

// Compile-time string conversion using array lookup (no branching)
template <ChronoDuration T>
constexpr std::string_view duration_type_name() noexcept
{
    using namespace std::chrono;

    if constexpr (std::is_same_v<T, seconds>)
        return "seconds";
    else if constexpr (std::is_same_v<T, milliseconds>)
        return "milliseconds";
    else if constexpr (std::is_same_v<T, microseconds>)
        return "microseconds";
    else if constexpr (std::is_same_v<T, nanoseconds>)
        return "nanoseconds";
    else
        return "custom_duration";
}

// CRTP base for static polymorphism
template <typename Derived>
class TimerBase
{
protected:
    using Clock = std::conditional_t<std::chrono::high_resolution_clock::is_steady, std::chrono::high_resolution_clock,
                                     std::chrono::steady_clock>;

    Clock::time_point m_start = Clock::now();
    std::string m_message;
    std::atomic<bool> m_is_stopped{false};

public:
    TimerBase() = default;
    explicit TimerBase(std::string message) : m_message(std::move(message)) {}

    TimerBase(const TimerBase&) = delete;
    TimerBase& operator=(const TimerBase&) = delete;
    TimerBase(TimerBase&&) = delete;
    TimerBase& operator=(TimerBase&&) = delete;

    ~TimerBase()
    {
        if (!m_is_stopped)
        {
            static_cast<Derived*>(this)->stop_impl();
        }
    }

    void start(std::string message)
    {
        m_message = std::move(message);
        m_is_stopped = false;
        m_start = Clock::now();
    }

protected:
    template <typename Resolution>
    void log_duration(const std::string& message) const
    {
        const auto end = Clock::now();
        const auto duration = std::chrono::duration_cast<Resolution>(end - m_start);

        // C++20 formatting (compile-time checked)
        std::cout << std::format("Time Elapsed for {} : {} {}\n", message, duration.count(),
                                 duration_type_name<Resolution>());
    }
};

// Main ExecutionTimer with configurable output
template <ChronoDuration Resolution = std::chrono::milliseconds>
class ExecutionTimer : public TimerBase<ExecutionTimer<Resolution>>
{
    using Base = TimerBase<ExecutionTimer<Resolution>>;
    friend Base;

public:
    using Base::Base;

private:
    void stop_impl()
    {
        this->template log_duration<Resolution>(this->m_message);
        this->m_is_stopped = true;
    }
};

// RAII-style scoped timer (zero overhead when disabled)
template <ChronoDuration Resolution = std::chrono::milliseconds>
class ScopedTimer
{
    using Clock = typename ExecutionTimer<Resolution>::Clock;
    Clock::time_point m_start;
    std::string_view m_message;

public:
    explicit ScopedTimer(std::string_view message) : m_start(Clock::now()), m_message(message) {}

    ~ScopedTimer()
    {
        const auto end = Clock::now();
        const auto duration = std::chrono::duration_cast<Resolution>(end - m_start);
        std::cout << std::format("Scoped [{}] : {} {}\n", m_message, duration.count(),
                                 duration_type_name<Resolution>());
    }
};

// Compile-time conditional timer (disabled in release builds)
#ifdef NDEBUG
#define DEBUG_TIMER(message) (void(0))
#else
#define DEBUG_TIMER(message) ScopedTimer debug_timer(message)
#endif

// Static timer for total accumulation
template <ChronoDuration Resolution = std::chrono::milliseconds>
class AccumulatingTimer
{
    using Clock = typename ExecutionTimer<Resolution>::Clock;
    Clock::time_point m_start;
    std::atomic<std::chrono::duration<double>> m_total{std::chrono::duration<double>::zero()};
    std::atomic<size_t> m_count{0};

public:
    class Session
    {
        AccumulatingTimer& m_parent;
        Clock::time_point m_start;

    public:
        explicit Session(AccumulatingTimer& parent) : m_parent(parent), m_start(Clock::now()) {}

        ~Session()
        {
            const auto end = Clock::now();
            m_parent.add(end - m_start);
        }
    };

    void add(std::chrono::duration<double> duration)
    {
        m_total.fetch_add(duration, std::memory_order_relaxed);
        m_count.fetch_add(1, std::memory_order_relaxed);
    }

    void report(std::string_view message = "Accumulated") const
    {
        auto total = m_total.load(std::memory_order_relaxed);
        auto count = m_count.load(std::memory_order_relaxed);
        auto avg = count > 0 ? total / count : std::chrono::duration<double>::zero();

        std::cout << std::format("{}: total={}ms avg={}ms calls={}\n", message,
                                 std::chrono::duration_cast<Resolution>(total).count(),
                                 std::chrono::duration_cast<Resolution>(avg).count(), count);
    }

    Session session()
    {
        return Session(*this);
    }
};

// Example usage
void example_usage()
{
    // Basic usage
    ExecutionTimer<> timer("Example operation");
    // ... do work
    timer.stop();

    // RAII style (auto-stops at scope exit)
    {
        ScopedTimer scope("Scope operation");
        // ... work
    }  // Auto logs here

    // Debug-only timing
    {
        DEBUG_TIMER("Debug operation");
        // Work that's only timed in debug builds
    }

    // Accumulating timer
    static AccumulatingTimer<microseconds> total_timer;
    for (int i = 0; i < 10; ++i)
    {
        auto session = total_timer.session();
        // Work to accumulate timing
    }
    total_timer.report("Total processing time");
}

// C++23: Even better with std::chrono::parse and std::print
#ifdef __cpp_lib_format
#include <print>

template <ChronoDuration Resolution = std::chrono::milliseconds>
void print_duration(auto duration)
{
    std::println("Time: {} {}", std::chrono::duration_cast<Resolution>(duration).count(),
                 duration_type_name<Resolution>());
}
#endif

// Optional: NullTimer for conditional compilation
class NullTimer
{
public:
    NullTimer() = default;
    explicit NullTimer(std::string_view) {}
    void start(std::string_view) {}
    void stop() const noexcept {}
};

// Conditional timer type (based on build config)
using ConditionalTimer = std::conditional_t<
#ifdef ENABLE_TIMING
    true,
#else
    false,
#endif
    ExecutionTimer<>, NullTimer>;

#endif  // TIMER_HPP
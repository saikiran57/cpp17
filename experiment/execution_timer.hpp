#pragma once

#include <chrono>
#include <sstream>
#include <string>

template <class Resolution = std::chrono::milliseconds>
class ExecutionTimer
{
public:
    using Clock = std::conditional_t<std::chrono::high_resolution_clock::is_steady, std::chrono::high_resolution_clock,
                                     std::chrono::steady_clock>;

private:
    const Clock::time_point mStart = Clock::now();

public:
    constexpr ExecutionTimer() = default;
    ~ExecutionTimer()
    {
        const auto end = Clock::now();
        std::ostringstream strStream;
        strStream << "Destructor Elapsed: " << std::chrono::duration_cast<Resolution>(end - mStart).count()
                  << std::endl;
        std::cout << strStream.str() << std::endl;
    }

    constexpr void stop()
    {
        const auto end = Clock::now();
        std::ostringstream strStream;
        strStream << "Stop Elapsed: " << std::chrono::duration_cast<Resolution>(end - mStart).count() << std::endl;
        std::cout << strStream.str() << std::endl;
    }
};  // ExecutionTimer
/**
 * @file time_request_counter.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-03-16
 *
 * @copyright Copyright (c) 2026
 *
 * @ref: https://medium.com/@naseefcse/efficient-request-counter-using-c-and-deque-52cdf95aa122
 */

#include <chrono>
#include <deque>
#include <iostream>

class RequestCounter
{
private:
    std::deque<std::chrono::steady_clock::time_point> requests;
    static constexpr std::chrono::seconds WINDOW_SIZE{40};

public:
    [[nodiscard]] std::size_t numRequest()
    {
        const auto now = std::chrono::steady_clock::now();

        // Remove requests older than window size
        while (!requests.empty() && (now - requests.front()) >= WINDOW_SIZE)
        {
            requests.pop_front();
        }

        // Add current request timestamp
        requests.push_back(now);

        return requests.size();
    }

    [[nodiscard]] std::size_t count() const
    {
        return requests.size();
    }

    void clear()
    {
        requests.clear();
    }
};

int main()
{
    RequestCounter counter;

    std::cout << counter.numRequest() << std::endl;  // 1
    std::cout << counter.numRequest() << std::endl;  // 2 (if called within 40s)

    return 0;
}
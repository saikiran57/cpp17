/**
 * @file events.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-08-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <chrono>
#include <condition_variable>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std::chrono_literals;

int process_events(const std::string& name)
{
    std::cout << "processing event: " << name;
    std::this_thread::sleep_for(1s);
    return 1;
}

std::future<int> async(std::function<int(const std::string&)> func)
{
    // create async method
    std::future<int> fut = std::async(func, "mytest");

    return fut;
}

class Events
{
public:
    Events() = default;
    ~Events()
    {
        std::unique_lock lk(m_mutex);
        while (m_pending_events != 0)
        {
            m_cv.wait(lk);
        }
    }

    void handle_event()
    {
        std::scoped_lock sl(m_mutex);
        ++m_pending_events;
        async(process_events);

        return;
    }

private:
    int m_pending_events;
    std::mutex m_mutex;
    std::condition_variable m_cv;
};
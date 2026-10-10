/**
 * @file write_counter.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-03-16
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <atomic>
#include <iostream>
#include <thread>

class write_counter
{
public:
    void increment() const
    {
        m_value.fetch_add(1, std::memory_order_relaxed);
    }

    int64_t get() const
    {
        return m_value.load(std::memory_order_relaxed);
    }

private:
    mutable std::atomic_int64_t m_value;
};

void worker(const write_counter& wc)
{
    for (auto i = 0; i < 1000000; ++i)
    {
        wc.increment();
    }
}

int main()
{
    write_counter wc;
    std::jthread p1(worker, std::ref(wc));
    std::jthread p2(worker, std::ref(wc));
    std::jthread p3(worker, std::ref(wc));
    std::jthread c(
        [](const write_counter& wc) {
            for (auto i = 0; i < 100; ++i)
            {
                // std::this_thread::sleep_for(std::chrono::milliseconds(10));
                std::cout << "value: " << wc.get() << "\n";
            }
        },
        std::ref(wc));

    return 0;
}
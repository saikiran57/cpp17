/**
 * @file basic_lock_free_queue.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-03-10
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <array>
#include <atomic>
#include <iostream>
#include <optional>
#include <thread>

template <class T, size_t N>
class LockFreeQueue
{
    std::array<T, N> buffer_{};    // Used by both threads
    std::atomic<size_t> size_{0};  // Used by both threads
    size_t read_pos_{0};           // Used by reader thread
    size_t write_pos_{0};          // Used by writer thread
    static_assert(std::atomic<size_t>::is_always_lock_free);
    bool do_push(auto&& t)
    {  // Helper function
        if (size_.load() == N)
        {
            return false;
        }
        buffer_[write_pos_] = std::forward<decltype(t)>(t);
        write_pos_ = (write_pos_ + 1) % N;
        size_.fetch_add(1);
        return true;
    }

public:
    // Writer thread
    bool push(T&& t)
    {
        return do_push(std::move(t));
    }
    bool push(const T& t)
    {
        return do_push(t);
    }
    // Reader thread
    auto pop() -> std::optional<T>
    {
        auto val = std::optional<T>{};
        if (size_.load() > 0)
        {
            val = std::move(buffer_[read_pos_]);
            read_pos_ = (read_pos_ + 1) % N;
            size_.fetch_sub(1);
        }
        return val;
    }
    // Both threads can call size()
    auto size() const noexcept
    {
        return size_.load();
    }
};

int main()
{
    LockFreeQueue<int, 100000> queue;

    std::thread producer([&queue]() {
        for (auto i = 0; i < 100; ++i)
        {
            queue.push(i);
        }
    });

    std::thread consumer([&queue]() {
        for (auto i = 0; i < 100; ++i)
        {
            std::cout << queue.pop().value_or(0) << "\n";
        }
    });

    producer.join();
    consumer.join();

    return 0;
}
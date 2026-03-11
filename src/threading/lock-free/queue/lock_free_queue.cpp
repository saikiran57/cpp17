#include <atomic>
#include <cassert>
#include <iostream>
#include <thread>
#include <vector>

template <typename T>
class LockFreeQueue
{
public:
    explicit LockFreeQueue(size_t capacity) : capacity(capacity), buffer(capacity), head(0), tail(0)
    {
        for (size_t i = 0; i < capacity; ++i)
        {
            buffer[i].occupied.store(false, std::memory_order_relaxed);
        }
    }

    // Producer: enqueue an item
    void enqueue(const T& item)
    {
        while (true)
        {
            size_t current_tail = tail.load(std::memory_order_relaxed);
            size_t next_tail = (current_tail + 1) % capacity;

            if (next_tail == head.load(std::memory_order_acquire))
            {
                // Queue full: wait until space is available
                std::atomic_wait_explicit(&tail, current_tail, std::memory_order_relaxed);
                continue;
            }

            Cell& cell = buffer[current_tail];
            bool expected = false;
            if (cell.occupied.compare_exchange_strong(expected, true, std::memory_order_release,
                                                      std::memory_order_relaxed))
            {
                cell.data = item;
                tail.store(next_tail, std::memory_order_release);
                std::atomic_notify_one(&head);  // wake up consumers
                return;
            }
        }
    }

    // Consumer: dequeue an item
    bool dequeue(T& result)
    {
        while (true)
        {
            size_t current_head = head.load(std::memory_order_relaxed);
            if (current_head == tail.load(std::memory_order_acquire))
            {
                // Queue empty: wait
                std::atomic_wait_explicit(&head, current_head, std::memory_order_relaxed);
                continue;
            }

            Cell& cell = buffer[current_head];
            bool expected = true;
            if (cell.occupied.compare_exchange_strong(expected, false, std::memory_order_acquire,
                                                      std::memory_order_relaxed))
            {
                result = std::move(cell.data);
                head.store((current_head + 1) % capacity, std::memory_order_release);
                std::atomic_notify_one(&tail);  // wake up producers
                return true;
            }
        }
    }

private:
    struct Cell
    {
        T data;
        std::atomic<bool> occupied;
    };

    const size_t capacity;
    std::vector<Cell> buffer;

    std::atomic<size_t> head;
    std::atomic<size_t> tail;
};

int main()
{
    LockFreeQueue<int> q(10);  // small capacity for demo

    auto producer = [&](std::stop_token st, int start) {
        for (int i = 0; i < 20; ++i)
        {
            q.enqueue(start + i);
        }
    };

    auto consumer = [&](std::stop_token st) {
        int count = 0;
        while (count < 20)
        {
            int val;
            if (q.dequeue(val))
            {
                std::cout << "Consumed: " << val << "\n";
                ++count;
            }
        }
    };

    std::jthread p1(producer, 100);
    std::jthread p2(producer, 200);
    std::jthread c1(consumer);
    std::jthread c2(consumer);

    // threads auto-join
}

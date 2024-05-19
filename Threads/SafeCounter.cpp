/**
 * @file SafeCounter.cpp
 * @author Saikiran Nadipilli
 * @brief https://en.cppreference.com/w/cpp/thread/shared_mutex
 * @version 0.1
 * @date 2024-03-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <mutex>
#include <shared_mutex> // c++17
#include <thread>

/**
 * @brief Thread Safe counter with shared mutex
 *
 * If one thread has acquired the exclusive lock (through lock, try_lock),
 * no other threads can acquire the lock (including the shared).
 * If one thread has acquired the shared lock (through lock_shared,
 * try_lock_shared), no other thread can acquire the exclusive lock, but can
 * acquire the shared lock.
 *
 * Within one thread, only one lock (shared or exclusive) can be acquired at the
 * same time.
 *
 * Shared mutexes are especially useful when shared data can be safely read by
 * any number of threads simultaneously, but a thread may only write the same
 * data when no other thread is reading or writing at the same time.
 *
 */
class SafeCounter {
public:
  void increment() {
    std::unique_lock lk(smu);
    ++value;
  }

  uint32_t get() const {
    std::shared_lock lk(smu);
    return value;
  }

private:
  mutable std::shared_mutex smu;
  uint32_t value{0};
};

int main() {
    SafeCounter counter;

    auto inc = [&](){
        for (size_t i = 0; i < 3; i++)
        {
            counter.increment();
            std::cout << std::this_thread::get_id() << ' ' << counter.get() << '\n';
        }
    };

    std::thread t1(inc);
    std::thread t2(inc);

    t1.join();
    t2.join();
}

#include <atomic>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <shared_mutex>
#include <string>
#include <thread>
#include <vector>

std::mutex mx;
std::condition_variable cv;
std::atomic<bool> shouldStop{false};

void cb(const std::string& s)
{
    std::cout << "ThreadId: " << std::this_thread::get_id() << " message: " << s << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

using CbFunc = std::function<void()>;

std::queue<std::string> taskQueue;

void workerThread()
{
    while (true)
    {
        std::unique_lock lk(mx);

        // Wait for a task or shutdown signal
        cv.wait(lk, [&]() {
            return !taskQueue.empty() || shouldStop;
        });

        // Exit if shutdown and no tasks left
        if (shouldStop && taskQueue.empty())
        {
            std::cout << "ThreadId: " << std::this_thread::get_id() << " exiting\n";
            break;
        }

        // Skip if queue is empty (spurious wakeup)
        if (taskQueue.empty())
        {
            continue;
        }

        std::cout << "ThreadId: " << std::this_thread::get_id() << " processing task\n";
        cb(taskQueue.front());
        taskQueue.pop();
        lk.unlock();
    }
}

int main()
{
    int threadCount = 4;
    std::vector<std::thread> tlist;
    tlist.reserve(threadCount);

    for (size_t i = 0; i < threadCount; i++)
    {
        tlist.push_back(std::thread{workerThread});
    }

    // Submit 10 tasks
    for (size_t i = 0; i < 10; i++)
    {
        std::string s = "my message " + std::to_string(i);
        {
            std::lock_guard lk(mx);
            taskQueue.push(s);
        }
        cv.notify_one();  // Notify one waiting thread per task
    }

    // Signal threads to stop and wake them all
    {
        std::lock_guard lk(mx);
        shouldStop = true;
    }
    cv.notify_all();

    // Wait for all threads to finish
    for (auto& t : tlist)
    {
        t.join();
    }

    std::cout << "All threads finished\n";
}

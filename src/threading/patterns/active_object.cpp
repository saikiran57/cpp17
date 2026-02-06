/**
 * @file active_object.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-08-15
 *
 * @copyright Copyright (c) 2025
 *
 * @ref: https://inpyjama.com/post/active-object-pattern/
 *
 */

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

// Active Object Class
class ActivePrinter
{
public:
    ActivePrinter() : is_running(true)
    {
        worker_thread = std::thread(&ActivePrinter::processMessages, this);
    }

    ~ActivePrinter()
    {
        is_running = false;
        condition.notify_one();
        worker_thread.join();
    }

    // Asynchronous Print Method
    void asyncPrint(const std::string& message)
    {
        std::unique_lock<std::mutex> lock(mutex);
        messages.push(message);
        condition.notify_one();
    }

private:
    std::queue<std::string> messages;
    std::thread worker_thread;
    std::mutex mutex;
    std::condition_variable condition;
    bool is_running;

    // Method to process messages from the queue
    void processMessages()
    {
        while (is_running)
        {
            std::unique_lock<std::mutex> lock(mutex);
            condition.wait(lock, [this]() {
                return !messages.empty() || !is_running;
            });

            if (!messages.empty())
            {
                std::string message = messages.front();
                messages.pop();
                lock.unlock();

                // Simulate time-consuming task (e.g., printing)
                std::this_thread::sleep_for(std::chrono::seconds(1));

                std::cout << "Printing: " << message << std::endl;
            }
        }
    }
};

int main()
{
    ActivePrinter printer;

    // Asynchronous print calls
    printer.asyncPrint("Document 1");
    printer.asyncPrint("Document 2");
    printer.asyncPrint("Document 3");

    // Other tasks can run concurrently with printing...

    // Wait for printing to complete
    std::this_thread::sleep_for(std::chrono::seconds(3));

    return 0;
}
/**
 * @file weak_threads.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-02-23
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <iostream>
#include <memory>
#include <thread>

std::thread observer;

void observe(std::weak_ptr<int> wp)
{
    // Start observer thread
    observer = std::thread([wp]() {
        std::cout << "calling thread...\n";
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));

            // Try acquiring a shared_ptr from weak_ptr
            if (std::shared_ptr<int> p = wp.lock())
            {
                // Success
                std::cout << "Observing: " << *p << "\n";
            }
            else
            {
                // The managed object is destroyed.
                std::cout << "Stop\n";
                break;
            }
        }
    });
}

int main()
{
    {  // Block Start
        auto sp = std::shared_ptr<int>(new int(10));
        // Create a weak_ptr<int> from sp for observing
        observe(sp);
        std::cout << "Calling in main\n";
        // Wait few seconds
        std::this_thread::sleep_for(std::chrono::seconds(5));

        // shared_ptr is destroyed and the
        //  managed object is deleted when
        //  block ends
    }

    // Wait for the observer thread to end
    observer.join();
    return 0;
}
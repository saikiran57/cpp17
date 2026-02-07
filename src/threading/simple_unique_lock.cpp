// C++ Program using std::unique_lock
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

// Global mutex to protect shared_data
mutex mtx;

// Shared data variable
int shared_data = 0;

// Function to increment shared_data
void increment_data()
{
    // Create a unique_lock object, but defer locking the mutex
    unique_lock<mutex> lock(mtx, defer_lock);

    // Explicitly acquire the lock
    lock.lock();

    // Critical section: safely modify shared_data
    shared_data += 2;

    // Manually release the lock
    lock.unlock();
}

int main()
{
    // Create two threads that run the increment_data function
    thread t1(increment_data);
    thread t2(increment_data);

    // Wait for both threads to finish
    t1.join();
    t2.join();

    // Output the value of shared_data
    cout << "Value of shared variable: " << shared_data;
    return 0;
}
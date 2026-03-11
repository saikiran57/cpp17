/**
 * @file async_logger.cpp
 * @author Saikiran Nadipilli (saikirannadipilli@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-02-24
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <iostream>
#include <memory>
#include <thread>

class Logger
{
public:
    void asyncLogger(const std::string& message)
    {
        // Capture current object as value (new copy is generated)
        std::thread([message, *this]() {
            std::cout << "before sleep Id: " << this->m_id << " message: " << message << "\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::cout << "Id: " << this->m_id << " message: " << message << "\n";
        }).detach();
    }
    int m_id = 11;
};

class Logger : public std::enable_shared_from_this<Logger>
{
public:
    void asyncLogger(const std::string& message)
    {
        //  Shared Lifetime Management: object is alive until thread finishes
        auto self = shared_from_this();
        std::thread([message, self]() {
            std::cout << "before sleep Id: " << self->m_id << " message: " << message << "\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::cout << "Id: " << self->m_id << " message: " << message << "\n";
        }).detach();
    }
    int m_id = 11;
};

class Logger : public std::enable_shared_from_this<Logger>
{
public:
    void asyncLogger(const std::string& message)
    {
        //  Weak Pointer Check (Best for Optional Operations): object is may or may not alive until thread finishes
        auto weakSelf = weak_from_this();
        std::thread([message, weakSelf]() {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            if (auto self = weakSelf.lock())
            {
                // Object still alive, use it
                std::cout << "Id: " << self->m_id << " message: " << message << "\n";
            }
            else
            {
                // Object destroyed, just log message
                std::cout << "Logger destroyed, message: " << message << "\n";
            }
        }).detach();
    }
    int m_id = 11;
};

// Approach	Lifetime	Object State	Use Case
// [*this]	Copy lives on	Can't access original	Thread needs own copy of data
// shared_from_this()	Keeps original alive	Always valid	Thread MUST have original object
// weak_from_this()	Original may die	Check before use	Optional operations

class AsyncWorker : public std::enable_shared_from_this<AsyncWorker>
{
public:
    void startWork()
    {
        auto self = shared_from_this();  // Keep self alive

        std::thread([self]() {  // Capture shared_ptr by value
            std::this_thread::sleep_for(std::chrono::seconds(2));
            self->doWork();  // Safe - object stays alive
        })
            .detach();
    }

private:
    void doWork()
    {
        std::cout << "Do work\n";
    }
};

// Key Takeaways
// *this capture creates a COPY - useful for small, copyable state

// Raw this in detached threads is DANGEROUS - object may be destroyed

// this != nullptr check is MEANINGLESS - doesn't validate original object

// Use shared_from_this() when thread MUST have the object

// Use weak_from_this() when operation is optional

// The rule of thumb: If your thread needs the original object, use shared_from_this(). If it just needs the data, copy
// what it needs, not the whole object!
int main()
{
    {
        Logger log;
        log.asyncLogger("Hello world");
    }
    std::cout << "After logger destroyed\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // Usage
    auto worker = std::make_shared<AsyncWorker>();
    worker->startWork();  // Thread keeps worker alive via shared_ptr
                          // worker.reset();  // Even if reset, thread still has a copy!
}
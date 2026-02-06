# Threading - Concurrency & Thread Synchronization

This directory contains comprehensive examples of multi-threaded programming in C++, including thread creation, synchronization, and concurrent patterns.

## Directory Structure

### Core Threading

- **basic.cpp** - Basic thread creation and management

  - Creating threads with functions and lambdas
  - Thread joining and detaching
  - Thread identifiers and attributes

- **simple_threads.cpp** - Simple thread examples

  - Multiple thread coordination
  - Basic thread lifecycle
  - Thread groups

- **events.cpp** - Event-based signaling
  - Condition variables for event notification
  - Wait and signal patterns
  - Spurious wakeup handling

### Synchronization Primitives

- **simple_unique_lock.cpp** - Lock wrapper example

  - RAII lock management
  - Automatic lock cleanup
  - Exception-safe locking

- **safe_counter.cpp** - Thread-safe counter implementation
  - Protected shared state
  - Atomic operations vs. locks
  - Performance considerations

### [mutex/](mutex/README.md) - Mutual Exclusion

- **std::mutex**: Basic mutual exclusion lock
- **std::recursive_mutex**: Reentrant locking
- **std::timed_mutex**: Locks with timeout
- **std::shared_mutex**: Readers-writer lock (C++17)
- Lock strategies and deadlock prevention

### [queue/](queue/README.md) - Thread-Safe Data Structures

- **Thread-safe queue**: Producer-consumer patterns
- **Lock-free structures**: Atomic-based synchronization
- **Concurrent queue**: Multiple producer/consumer
- **Performance optimization**: Batch operations

### [patterns/](patterns/README.md) - Concurrency Patterns

- **Producer-consumer**: Classic synchronization pattern
- **Reader-writer**: Multiple readers, single writer
- **Thread pool**: Work queue with thread management
- **Monitor pattern**: Synchronized access to shared resource
- **Barrier**: Synchronization point for multiple threads

### Packaged Tasks & Futures

- **packaged_task.cpp** - Task packaging and async execution
  - Wrapping callable objects
  - Future result retrieval
  - Exception propagation from threads

## Key Concepts

### Thread Safety Levels

1. **Thread-unsafe**: No synchronization, data races possible
2. **Thread-safe (reads)**: Multiple readers OK, exclusive write
3. **Thread-safe (serialized)**: Exclusive access required
4. **Thread-safe (lock-free)**: Atomic operations, no explicit locks

### Synchronization Primitives

- **Mutex**: Binary lock, one owner at a time
- **Recursive Mutex**: Same thread can acquire multiple times
- **Shared Mutex**: Multiple readers OR one writer
- **Condition Variable**: Notify waiting threads of events
- **Atomic**: Lock-free synchronization for simple types
- **Semaphore**: Counter-based signaling (C++20)
- **Latch**: One-time synchronization point (C++20)
- **Barrier**: Reusable synchronization point (C++20)

### Lock Types

- **lock_guard**: RAII lock, non-movable
- **unique_lock**: RAII lock with timeout and flexibility
- **shared_lock**: RAII read lock for shared_mutex
- **scoped_lock**: RAII multi-lock acquisition (C++17)

### Atomic Operations

- Lock-free synchronization for integral and pointer types
- Relaxed, acquire, release, and sequential consistency memory ordering
- Compare-and-swap for optimistic synchronization

## Building Examples

Compile with threading support:

```bash
g++ -std=c++17 -pthread -o output filename.cpp
```

Enable thread sanitizer for debugging:

```bash
g++ -std=c++17 -pthread -fsanitize=thread -g -o output filename.cpp
```

## Learning Path

1. Start with **basic.cpp** - Thread fundamentals
2. Learn **simple_threads.cpp** - Multiple threads
3. Study **simple_unique_lock.cpp** - Locking mechanisms
4. Master **mutex/** - Mutual exclusion strategies
5. Explore **packaged_task.cpp** - Async execution
6. Learn **safe_counter.cpp** - Atomic alternatives
7. Study **patterns/** - High-level patterns
8. Advance to **queue/** - Thread-safe containers

## Common Patterns

### Protecting Shared State

```cpp
class Counter {
    mutable std::mutex m_;
    int count_ = 0;
public:
    int get() const {
        std::lock_guard<std::mutex> lock(m_);
        return count_;
    }
    void increment() {
        std::lock_guard<std::mutex> lock(m_);
        ++count_;
    }
};
```

### Wait for Condition

```cpp
std::condition_variable cv;
std::mutex m;
bool ready = false;

// Waiter
{
    std::unique_lock<std::mutex> lock(m);
    cv.wait(lock, [] { return ready; });
    // use shared resource
}

// Notifier
{
    std::lock_guard<std::mutex> lock(m);
    ready = true;
}
cv.notify_one();
```

### Async Execution with Future

```cpp
std::packaged_task<int()> task([]{ return 42; });
std::future<int> f = task.get_future();

std::thread t(std::move(task));
int result = f.get(); // Wait for result
t.join();
```

## Performance Considerations

- ✅ Use atomic operations for simple types (faster than mutex)
- ✅ Use read-write locks when reads >> writes
- ✅ Minimize lock scope to reduce contention
- ✅ Use lock-free structures when possible
- ✅ Avoid nested locks (deadlock prevention)
- ✅ Use condition variables for event notification
- ✅ Consider thread pool for many small tasks

## Common Pitfalls

1. **Data races**: Accessing shared data without synchronization
2. **Deadlock**: Circular lock dependencies
3. **Spurious wakeups**: condition_variable may wake without notification
4. **Use-after-free**: Thread accesses destroyed objects
5. **Race conditions**: Check-then-act sequences without atomicity
6. **Exception safety**: Exceptions in locked sections cause deadlock
7. **Priority inversion**: Low-priority thread blocks high-priority thread

## Best Practices

- ✅ Always use RAII locks (lock_guard, unique_lock, scoped_lock)
- ✅ Check condition variables in a loop (spurious wakeup)
- ✅ Use `std::call_once` for one-time initialization
- ✅ Prefer condition variables over polling
- ✅ Use atomic types for simple flags
- ✅ Document thread safety level of all functions
- ✅ Test with thread sanitizer and race detector
- ✅ Use thread pool for efficient thread management

## Debugging Tools

- **Thread Sanitizer**: `-fsanitize=thread` detects data races
- **Helgrind (Valgrind)**: Memory and threading error detector
- **ThreadSanitizer**: Google's thread race detector
- **Intel Inspector**: Commercial thread debugging tool
- **gdb/lldb**: Built-in thread debugging commands

## Related Topics

- [Basics - Lambda](../basics/lambda.cpp) - Lambdas in threads
- [STL - Functional](../stl/functional/README.md) - Callable objects
- [Advanced Patterns](patterns/README.md) - High-level concurrency patterns

---

**Back to**: [Source Directory](../README.md) | [Main README](../../README.md)

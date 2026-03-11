#include <array>
#include <atomic>
#include <cstddef>
#include <optional>
#include <utility>

/**
 * @brief
 *  Why This Queue Is Faster
 * 1️⃣ No shared counter (size_)
 * 2️⃣ Single writer per atomic
 * 3️⃣ Acquire / Release Synchronization
 * 4️⃣ Power-of-Two Optimization
 * 5️⃣ Cache Line Padding
 */

template <typename T, size_t N>
class spsc_queue
{
    static_assert((N & (N - 1)) == 0, "N must be power of two");

    alignas(64) std::atomic<size_t> write_index_{0};
    alignas(64) std::atomic<size_t> read_index_{0};

    std::array<T, N> buffer_;

public:
    bool push(T value)
    {
        size_t write = write_index_.load(std::memory_order_relaxed);
        size_t next = (write + 1) & (N - 1);

        if (next == read_index_.load(std::memory_order_acquire)) return false;  // queue full

        buffer_[write] = std::move(value);

        write_index_.store(next, std::memory_order_release);

        return true;
    }

    std::optional<T> pop()
    {
        size_t read = read_index_.load(std::memory_order_relaxed);

        if (read == write_index_.load(std::memory_order_acquire)) return std::nullopt;  // empty

        T value = std::move(buffer_[read]);

        size_t next = (read + 1) & (N - 1);

        read_index_.store(next, std::memory_order_release);

        return value;
    }

    bool empty() const
    {
        return read_index_.load(std::memory_order_acquire) == write_index_.load(std::memory_order_acquire);
    }
};
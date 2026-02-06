#include <chrono>
#include <iostream>

volatile int sink = 0;

// ================================================================
// CRTP
// ================================================================
template <typename Derived>
class ImageCRTP
{
public:
    __attribute__((always_inline)) inline void Draw()
    {
        static_cast<Derived*>(this)->DrawImpl();
    }
};

class TiffImageCRTP final : public ImageCRTP<TiffImageCRTP>
{
public:
    __attribute__((always_inline)) inline void DrawImpl() const
    {
        // Heavy work to amplify dispatch overhead
        sink += 1;
        sink *= 7;
        sink ^= 0x1234;
        sink -= 3;
    }
};

// ================================================================
// Virtual — force NO INLINE and NO devirtualization
// ================================================================
class ImageVirtual
{
public:
    virtual void Draw() __attribute__((noinline));  // enforce no inline
    virtual ~ImageVirtual() = default;
};

void ImageVirtual::Draw() {}  // abstract behavior overridden

class TiffImageVirtual final : public ImageVirtual
{
public:
    void Draw() override __attribute__((noinline))
    {
        sink += 1;
        sink *= 7;
        sink ^= 0x1234;
        sink -= 3;
    }
};

// ================================================================
// Benchmark
// ================================================================
template <typename Func>
uint64_t Benchmark(const char* title, Func f)
{
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

// ================================================================
// MAIN
// ================================================================
int main()
{
    constexpr int N = 80'000'000;

    // CRTP — best case (direct static type)
    TiffImageCRTP crtp;

    // Virtual — stored via pointer (cannot be devirtualized)
    ImageVirtual* virt = new TiffImageVirtual();

    auto crtp_time = Benchmark("CRTP Draw()", [&] {
        for (int i = 0; i < N; ++i)
            crtp.Draw();
    });

    auto virt_time = Benchmark("Virtual Draw()", [&] {
        for (int i = 0; i < N; ++i)
            virt->Draw();
    });

    std::cout << "CRTP Draw():   " << crtp_time << " ns\n";
    std::cout << "Virtual Draw(): " << virt_time << " ns\n";

    delete virt;
}

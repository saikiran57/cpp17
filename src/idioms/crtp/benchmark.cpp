#include <chrono>
#include <cstdint>
#include <iostream>
#include <memory>

// -------------------------------------------------------------
//  Helper to prevent compiler from optimizing away the function calls
// -------------------------------------------------------------
volatile int sink = 0;

// -------------------------------------------------------------
//  CRTP Version
// -------------------------------------------------------------
template <typename Derived>
class ImageCRTP
{
public:
    void Draw()
    {
        static_cast<Derived*>(this)->Draw();
    }
    int GetVal()
    {
        return static_cast<Derived*>(this)->GetVal();
    }
};

class TiffImageCRTP : public ImageCRTP<TiffImageCRTP>
{
public:
    void Draw()
    {
        sink++;  // prevent optimization
    }
    int GetVal()
    {
        return 42;
    }
};

// -------------------------------------------------------------
//  Virtual Version
// -------------------------------------------------------------
class ImageVirtual
{
public:
    virtual ~ImageVirtual() = default;
    virtual void Draw() = 0;
    virtual int GetVal() = 0;
};

class TiffImageVirtual : public ImageVirtual
{
public:
    void Draw() override
    {
        sink++;  // prevent optimization
    }
    int GetVal() override
    {
        return 42;
    }
};

// -------------------------------------------------------------
// Benchmark function
// -------------------------------------------------------------
template <typename Func>
uint64_t Benchmark(const char* title, Func f)
{
    auto start = std::chrono::steady_clock::now();
    f();
    auto end = std::chrono::steady_clock::now();

    uint64_t ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << title << ": " << ns << " ns\n";
    return ns;
}

// -------------------------------------------------------------
//  Main
// -------------------------------------------------------------
int main()
{
    constexpr int N = 50'000'000;  // 50 million calls

    // --- CRTP instance ---
    TiffImageCRTP crtpObj;
    ImageCRTP<TiffImageCRTP>* crtpPtr = &crtpObj;

    // --- Virtual instance ---
    TiffImageVirtual virtualObj;
    ImageVirtual* virtualPtr = &virtualObj;

    // ---------------------------------------------------------
    // Benchmark CRTP
    // ---------------------------------------------------------
    Benchmark("CRTP Draw()", [&]() {
        for (int i = 0; i < N; ++i)
            crtpPtr->Draw();
    });

    Benchmark("CRTP GetVal()", [&]() {
        for (int i = 0; i < N; ++i)
            sink += crtpPtr->GetVal();
    });

    // ---------------------------------------------------------
    // Benchmark VIRTUAL
    // ---------------------------------------------------------
    Benchmark("Virtual Draw()", [&]() {
        for (int i = 0; i < N; ++i)
            virtualPtr->Draw();
    });

    Benchmark("Virtual GetVal()", [&]() {
        for (int i = 0; i < N; ++i)
            sink += virtualPtr->GetVal();
    });

    return 0;
}

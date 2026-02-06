#include "better_benchmark.hpp"
#include <memory>
#include <vector>

class HighResTimer
{
    std::chrono::high_resolution_clock::time_point start_;
    std::string name_;

public:
    HighResTimer(const std::string& name) : name_(name)
    {
        start_ = std::chrono::high_resolution_clock::now();
    }
    ~HighResTimer()
    {
        auto end = std::chrono::high_resolution_clock::now();
        auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start_);
        std::cout << name_ << ": " << ns.count() << " ns (" << (ns.count() / 1000000.0) << " ms)\n";
    }
};

// Scenario 1: Simple loop - compiler CAN devirtualize
void benchmarkVirtualScenario1(int iterations)
{
    std::vector<VirtualShape*> shapes;

    // Create a predictable pattern
    for (int i = 0; i < iterations; ++i)
    {
        switch (i % 3)
        {
            case 0:
                shapes.push_back(new VirtualCircle(i + 1));
                break;
            case 1:
                shapes.push_back(new VirtualRectangle(i + 1, i + 2));
                break;
            case 2:
                shapes.push_back(new VirtualTriangle(i + 1, i + 2, i + 3));
                break;
        }
    }

    double total = 0;
    {
        HighResTimer timer("Virtual Scenario 1");
        for (int i = 0; i < iterations; ++i)
        {
            total += shapes[i]->area();
            shapes[i]->scale(1.01);
            total += shapes[i]->perimeter();
        }
    }

    // Cleanup
    for (auto s : shapes)
        delete s;

    std::cout << "  (Result: " << total << ")\n";
}

void benchmarkCRTPScenario1(int iterations)
{
    std::vector<CRTPCircle> circles;
    std::vector<CRTPRectangle> rects;
    std::vector<CRTPTriangle> triangles;

    circles.reserve(iterations / 3 + 1);
    rects.reserve(iterations / 3 + 1);
    triangles.reserve(iterations / 3 + 1);

    for (int i = 0; i < iterations; ++i)
    {
        switch (i % 3)
        {
            case 0:
                circles.emplace_back(i + 1);
                break;
            case 1:
                rects.emplace_back(i + 1, i + 2);
                break;
            case 2:
                triangles.emplace_back(i + 1, i + 2, i + 3);
                break;
        }
    }

    double total = 0;
    {
        HighResTimer timer("CRTP Scenario 1");
        int ci = 0, ri = 0, ti = 0;
        for (int i = 0; i < iterations; ++i)
        {
            switch (i % 3)
            {
                case 0:
                    total += circles[ci].area();
                    circles[ci].scale(1.01);
                    total += circles[ci].perimeter();
                    ci++;
                    break;
                case 1:
                    total += rects[ri].area();
                    rects[ri].scale(1.01);
                    total += rects[ri].perimeter();
                    ri++;
                    break;
                case 2:
                    total += triangles[ti].area();
                    triangles[ti].scale(1.01);
                    total += triangles[ti].perimeter();
                    ti++;
                    break;
            }
        }
    }

    std::cout << "  (Result: " << total << ")\n";
}

// Scenario 2: REAL polymorphism - compiler CANNOT devirtualize
void benchmarkVirtualScenario2()
{
    std::vector<std::unique_ptr<VirtualShape>> shapes;

    // Create random shapes - compiler cannot predict
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(0, 2);

    const int count = 1000000;
    shapes.reserve(count);

    for (int i = 0; i < count; ++i)
    {
        switch (dist(rng))
        {
            case 0:
                shapes.push_back(std::make_unique<VirtualCircle>(i % 10 + 1));
                break;
            case 1:
                shapes.push_back(std::make_unique<VirtualRectangle>(i % 10 + 1, i % 10 + 2));
                break;
            case 2:
                shapes.push_back(std::make_unique<VirtualTriangle>(i % 10 + 1, i % 10 + 2, i % 10 + 3));
                break;
        }
    }

    double total = 0;
    {
        HighResTimer timer("Virtual Scenario 2 (Random)");
        // This loop CANNOT be devirtualized - random access pattern
        for (auto& shape : shapes)
        {
            total += shape->area();
            shape->scale(1.001);
            total += shape->perimeter();
        }
    }

    std::cout << "  (Result: " << total << ")\n";
}

// For CRTP, we can't have true random polymorphism in one container
// This shows the limitation of CRTP
void benchmarkCRTPScenario2()
{
    std::vector<CRTPCircle> circles;
    std::vector<CRTPRectangle> rects;
    std::vector<CRTPTriangle> triangles;

    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(0, 2);

    const int count = 1000000;

    for (int i = 0; i < count; ++i)
    {
        switch (dist(rng))
        {
            case 0:
                circles.emplace_back(i % 10 + 1);
                break;
            case 1:
                rects.emplace_back(i % 10 + 1, i % 10 + 2);
                break;
            case 2:
                triangles.emplace_back(i % 10 + 1, i % 10 + 2, i % 10 + 3);
                break;
        }
    }

    double total = 0;
    {
        HighResTimer timer("CRTP Scenario 2 (Separate containers)");
        for (auto& circle : circles)
        {
            total += circle.area();
            circle.scale(1.001);
            total += circle.perimeter();
        }
        for (auto& rect : rects)
        {
            total += rect.area();
            rect.scale(1.001);
            total += rect.perimeter();
        }
        for (auto& tri : triangles)
        {
            total += tri.area();
            tri.scale(1.001);
            total += tri.perimeter();
        }
    }

    std::cout << "  (Result: " << total << ")\n";
}

void runRealisticBenchmarks()
{
    std::cout << "\n============================================\n";
    std::cout << "REALISTIC CRTP vs Virtual Benchmarks\n";
    std::cout << "============================================\n\n";

    std::cout << "SCENARIO 1: Predictable pattern (devirtualization possible)\n";
    std::cout << "--------------------------------------------------------\n";
    benchmarkVirtualScenario1(1000000);
    benchmarkCRTPScenario1(1000000);

    std::cout << "\nSCENARIO 2: Random polymorphism (NO devirtualization)\n";
    std::cout << "----------------------------------------------------\n";
    benchmarkVirtualScenario2();
    benchmarkCRTPScenario2();

    std::cout << "\n============================================\n";
    std::cout << "KEY INSIGHTS:\n";
    std::cout << "============================================\n";
    std::cout << "1. With -O3, simple virtual calls ARE devirtualized\n";
    std::cout << "2. CRTP shines when:\n";
    std::cout << "   - Compiler can't devirtualize (complex patterns)\n";
    std::cout << "   - You need small, hot loops optimized\n";
    std::cout << "   - You can live without runtime polymorphism\n";
    std::cout << "3. Virtual is better when:\n";
    std::cout << "   - You need true runtime polymorphism\n";
    std::cout << "   - You have plugin architectures\n";
    std::cout << "   - Code simplicity matters more than last 10% perf\n";
    std::cout << "\nRECOMMENDATION:\n";
    std::cout << "- Start with virtual (it's clearer, more flexible)\n";
    std::cout << "- Only use CRTP if profiling shows virtual calls are bottleneck\n";
    std::cout << "============================================\n";
}
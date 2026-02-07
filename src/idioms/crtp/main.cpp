#include "better_benchmark.hpp"

int main()
{
    runRealisticBenchmarks();

    // Show the difference in code design
    std::cout << "\n\nDesign Difference Example:\n";

    // Virtual allows this:
    std::vector<std::unique_ptr<VirtualShape>> shapes;
    shapes.push_back(std::make_unique<VirtualCircle>(5));
    shapes.push_back(std::make_unique<VirtualRectangle>(3, 4));
    shapes.push_back(std::make_unique<VirtualTriangle>(3, 4, 5));

    std::cout << "\nVirtual (true polymorphism):\n";
    for (auto& shape : shapes)
    {
        std::cout << shape->name() << ": Area = " << shape->area() << "\n";
    }

    // CRTP cannot do this in one container:
    std::cout << "\nCRTP (separate containers):\n";
    CRTPCircle c(5);
    CRTPRectangle r(3, 4);
    CRTPTriangle t(3, 4, 5);

    std::cout << c.name() << ": Area = " << c.area() << "\n";
    std::cout << r.name() << ": Area = " << r.area() << "\n";
    std::cout << t.name() << ": Area = " << t.area() << "\n";

    return 0;
}
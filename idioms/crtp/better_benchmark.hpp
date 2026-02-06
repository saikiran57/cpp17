#pragma once
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

// More realistic base class
class VirtualShape
{
public:
    virtual ~VirtualShape() = default;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void scale(double factor) = 0;
    virtual std::string name() const = 0;
};

class VirtualCircle : public VirtualShape
{
    double radius_;

public:
    VirtualCircle(double r) : radius_(r) {}
    double area() const override
    {
        return 3.14159 * radius_ * radius_;
    }
    double perimeter() const override
    {
        return 2 * 3.14159 * radius_;
    }
    void scale(double factor) override
    {
        radius_ *= factor;
    }
    std::string name() const override
    {
        return "Circle";
    }
};

class VirtualRectangle : public VirtualShape
{
    double width_, height_;

public:
    VirtualRectangle(double w, double h) : width_(w), height_(h) {}
    double area() const override
    {
        return width_ * height_;
    }
    double perimeter() const override
    {
        return 2 * (width_ + height_);
    }
    void scale(double factor) override
    {
        width_ *= factor;
        height_ *= factor;
    }
    std::string name() const override
    {
        return "Rectangle";
    }
};

class VirtualTriangle : public VirtualShape
{
    double a_, b_, c_;

public:
    VirtualTriangle(double a, double b, double c) : a_(a), b_(b), c_(c) {}
    double area() const override
    {
        double s = (a_ + b_ + c_) / 2;
        return sqrt(s * (s - a_) * (s - b_) * (s - c_));
    }
    double perimeter() const override
    {
        return a_ + b_ + c_;
    }
    void scale(double factor) override
    {
        a_ *= factor;
        b_ *= factor;
        c_ *= factor;
    }
    std::string name() const override
    {
        return "Triangle";
    }
};

// CRTP Implementation
template <typename Derived>
class ShapeCRTP
{
public:
    double area() const
    {
        return static_cast<const Derived*>(this)->areaImpl();
    }
    double perimeter() const
    {
        return static_cast<const Derived*>(this)->perimeterImpl();
    }
    void scale(double factor)
    {
        static_cast<Derived*>(this)->scaleImpl(factor);
    }
    std::string name() const
    {
        return static_cast<const Derived*>(this)->nameImpl();
    }
};

class CRTPCircle : public ShapeCRTP<CRTPCircle>
{
    double radius_;

public:
    CRTPCircle(double r) : radius_(r) {}
    double areaImpl() const
    {
        return 3.14159 * radius_ * radius_;
    }
    double perimeterImpl() const
    {
        return 2 * 3.14159 * radius_;
    }
    void scaleImpl(double factor)
    {
        radius_ *= factor;
    }
    std::string nameImpl() const
    {
        return "Circle";
    }
};

class CRTPRectangle : public ShapeCRTP<CRTPRectangle>
{
    double width_, height_;

public:
    CRTPRectangle(double w, double h) : width_(w), height_(h) {}
    double areaImpl() const
    {
        return width_ * height_;
    }
    double perimeterImpl() const
    {
        return 2 * (width_ + height_);
    }
    void scaleImpl(double factor)
    {
        width_ *= factor;
        height_ *= factor;
    }
    std::string nameImpl() const
    {
        return "Rectangle";
    }
};

class CRTPTriangle : public ShapeCRTP<CRTPTriangle>
{
    double a_, b_, c_;

public:
    CRTPTriangle(double a, double b, double c) : a_(a), b_(b), c_(c) {}
    double areaImpl() const
    {
        double s = (a_ + b_ + c_) / 2;
        return sqrt(s * (s - a_) * (s - b_) * (s - c_));
    }
    double perimeterImpl() const
    {
        return a_ + b_ + c_;
    }
    void scaleImpl(double factor)
    {
        a_ *= factor;
        b_ *= factor;
        c_ *= factor;
    }
    std::string nameImpl() const
    {
        return "Triangle";
    }
};

// Benchmark scenarios
void benchmarkVirtualScenario1(int iterations);
void benchmarkCRTPScenario1(int iterations);
void benchmarkVirtualScenario2();  // Real polymorphism
void benchmarkCRTPScenario2();     // No true polymorphism possible
void runRealisticBenchmarks();
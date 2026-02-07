# Idioms - C++ Design Patterns & Idioms

This directory contains implementations of C++ design patterns and idioms, showcasing best practices and elegant solutions to common problems.

## Directory Structure

### [crtp/](crtp/README.md)

**CRTP - Curiously Recurring Template Pattern**

A powerful idiom for static polymorphism:

- Override function mechanism without virtual functions
- Compile-time polymorphism for zero-overhead abstraction
- CRTP base class pattern
- Static dispatch vs. dynamic dispatch comparison
- Performance benefits and use cases

## Key Patterns & Idioms

### Structural Patterns

#### Inheritance

- Single inheritance
- Multiple inheritance
- Virtual inheritance
- Interface design

#### Composition

- Object composition over inheritance
- Wrapper objects
- Has-a relationships

### Behavioral Patterns

#### Strategy Pattern

- Runtime algorithm selection
- Function objects and lambdas
- Strategy interface

#### Observer Pattern

- Event notification system
- Observer registration and removal
- Decoupled event handling

#### Factory Pattern

- Object creation abstraction
- Factory functions
- Factory classes

### Modern C++ Idioms

#### RAII (Resource Acquisition Is Initialization)

- Resources tied to object lifetime
- Automatic cleanup in destructors
- Exception safety

#### Move Semantics

- Efficient resource transfer
- Move constructors and assignment
- Perfect forwarding

#### PIMPL (Pointer to Implementation)

- Hide implementation details
- Reduce compilation dependencies
- Binary compatibility

#### Crtp (Curiously Recurring Template Pattern)

- Static polymorphism without virtual functions
- Compile-time type information
- Zero-overhead abstraction

## Best Practices

### Design Principles

- **Single Responsibility**: Classes should have one reason to change
- **Open/Closed Principle**: Open for extension, closed for modification
- **Liskov Substitution**: Derived classes should be substitutable
- **Interface Segregation**: Clients shouldn't depend on unused interfaces
- **Dependency Inversion**: Depend on abstractions, not concretions

### C++ Specific

- ✅ Prefer composition over inheritance
- ✅ Use virtual functions only when necessary
- ✅ Use RAII for resource management
- ✅ Use move semantics for efficient transfers
- ✅ Use const-correctness throughout
- ✅ Use smart pointers instead of raw pointers
- ✅ Use algorithms instead of manual loops
- ✅ Use CRTP for static polymorphism when appropriate

### Anti-Patterns to Avoid

- ❌ Deep inheritance hierarchies
- ❌ God objects with too many responsibilities
- ❌ Visible members and protected access
- ❌ Unnecessary virtual functions
- ❌ Raw pointers for ownership
- ❌ Global state and singletons
- ❌ Non-const references for input parameters

## Pattern Categories

### Creational Patterns

- Singleton
- Factory
- Builder
- Prototype
- Object pool

### Structural Patterns

- Adapter
- Decorator
- Facade
- Proxy
- Bridge
- Composite
- Flyweight

### Behavioral Patterns

- Chain of responsibility
- Command
- Iterator
- Mediator
- Memento
- Observer
- State
- Strategy
- Template Method
- Visitor

## Common C++ Idioms

### Copy-and-Swap

```cpp
class MyClass {
    MyClass& operator=(MyClass temp) {
        swap(*this, temp);
        return *this;
    }
};
```

### PIMPL (Private Implementation)

```cpp
class Widget {
    struct Impl;
    std::unique_ptr<Impl> pimpl_;
};
```

### CRTP

```cpp
template<typename Derived>
class Base {
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
};

class Derived : public Base<Derived> {
    void implementation() { /* ... */ }
};
```

## Building Examples

Compile any file with:

```bash
g++ -std=c++17 -o output filename.cpp
```

## Learning Path

1. Review design principles and SOLID
2. Study RAII for resource management
3. Learn CRTP for static polymorphism
4. Explore specific patterns relevant to your domain
5. Understand trade-offs between patterns
6. Practice applying patterns to new problems

## When to Use Each Pattern

| Problem                 | Pattern  | Pros                     | Cons                       |
| ----------------------- | -------- | ------------------------ | -------------------------- |
| Create complex objects  | Builder  | Flexible, readable       | Verbose                    |
| Hide implementation     | PIMPL    | Decoupled, ABI stable    | Runtime indirection        |
| Avoid virtual calls     | CRTP     | Zero overhead, type-safe | Complex, compile-time only |
| Algorithm selection     | Strategy | Flexible at runtime      | Runtime overhead           |
| Notify multiple objects | Observer | Loose coupling           | Complex communication flow |

## Related Topics

- [Basics - OOP](../basics/vtable.cpp) - Virtual functions and inheritance
- [Basics - Move Semantics](../basics/move.cpp) - Efficient resource transfer
- [Templates - Advanced](../templates/README.md) - Template techniques
- [STL - Functional](../stl/functional/README.md) - Function objects and callbacks

## Resources

- "Design Patterns: Elements of Reusable Object-Oriented Software" by Gang of Four
- "Modern C++ Design" by Andrei Alexandrescu
- "Effective C++" series by Scott Meyers
- "C++ Coding Standards" by Herb Sutter and Andrei Alexandrescu

---

**Back to**: [Source Directory](../README.md) | [Main README](../../README.md)

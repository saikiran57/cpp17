# Basics - Core C++ Language Features

This directory contains examples and implementations of fundamental C++ language features and core concepts essential for understanding C++17.

## Contents Overview

### Type System & Casting

- **casting.cpp** - Type casting (static_cast, dynamic_cast, reinterpret_cast, const_cast)
- **typeid.cpp** - Runtime type information (RTTI)
- **decltype.cpp** - Type deduction at compile time

### Variables & References

- **reference.cpp** - Reference semantics and usage
- **this_pointer.cpp** - Understanding the this pointer in class context

### Object-Oriented Programming

- **basic_class.cpp** - Class design and member functions
- **vtable.cpp** - Virtual function table mechanism
- **custom_vtable1.cpp** - Custom virtual function implementation
- **variant.cpp** - Type-safe union (std::variant)

### Modern C++ Features

- **constexpr.cpp** - Compile-time computation
- **in_place.cpp** - In-place construction
- **lambda.cpp** - Lambda expressions and closures
- **inline.cpp** - Inline function optimization

### Memory Management

- **memory/** - Subdirectory with memory management examples
  - Smart pointers
  - Allocators
  - RAII (Resource Acquisition Is Initialization)

### Move Semantics

- **move.cpp** - Move semantics and move constructors
- **move_if_noexcept.cpp** - Conditional move semantics
- **move_if_noexcept_ii.cpp** - Advanced move semantics examples
- **bugprone-use-after-move.cpp** - Common pitfalls with move semantics

### Exception Handling

- **exceptions/** - Exception handling patterns and best practices

### Utility Features

- **hash.cpp** - Hash function implementation
- **common.cpp** - Common utility functions

### Advanced Topics

- **allocators/** - Custom memory allocators
  - Pool allocators
  - Stack allocators
  - Custom allocation strategies
- **bits/** - Bit manipulation examples
- **primitives/** - Primitive type usage and limitations
- **strings/** - String manipulation and utilities
- **casting/** - Detailed casting examples

## Key Concepts

### Type Safety

C++ provides multiple ways to ensure type safety at compile-time and runtime.

### References vs Pointers

- References are safer and cleaner than raw pointers
- References cannot be null or rebound
- Use references for function parameters and return values

### Move Semantics

- Enables efficient transfer of resources
- Critical for performance in C++11 and later
- Use `std::move()` carefully to avoid use-after-move bugs

### RAII Pattern

- Resource Acquisition Is Initialization
- Ensures proper resource cleanup
- Exception-safe code through smart pointers

### Exception Safety

- Basic guarantee: invariants maintained
- Strong guarantee: all-or-nothing semantics
- Nothrow guarantee: function never throws

## Building Examples

Compile any file with:

```bash
g++ -std=c++17 -o output filename.cpp
```

Run the compiled program:

```bash
./output
```

## Learning Path

1. Start with **basic_class.cpp** - Understanding classes
2. Learn **casting.cpp** - Type system
3. Study **reference.cpp** - Reference semantics
4. Explore **lambda.cpp** - Modern function syntax
5. Understand **move.cpp** - Move semantics
6. Review **vtable.cpp** - Object model internals
7. Dive into **memory/** - Memory management patterns
8. Study **exceptions/** - Error handling

## Related Topics

- [Templates](../templates/README.md) - Type-safe abstractions
- [STL](../stl/README.md) - Container and algorithm usage
- [Memory Management Details](../stl/containers/README.md)

## Common Pitfalls

1. **Use-after-move**: Accessing moved-from objects
2. **Dangling references**: Returning references to temporary objects
3. **Exception safety**: Non-exception-safe code in destructors
4. **Memory leaks**: Forgetting to delete dynamically allocated memory (use smart pointers instead)
5. **Slicing**: Implicitly converting derived to base class

## Best Practices

- ✅ Use references instead of pointers for non-nullable parameters
- ✅ Use smart pointers (unique_ptr, shared_ptr) instead of raw pointers
- ✅ Mark functions as `const` when they don't modify state
- ✅ Use `constexpr` for compile-time computation
- ✅ Prefer lambdas over function objects for simple callbacks
- ✅ Use move semantics to avoid unnecessary copies
- ✅ Follow RAII for resource management

---

**Back to**: [Source Directory](../README.md) | [Main README](../../README.md)

# Source Code Directory

This directory contains the main source code organized by topic. Each subdirectory covers a specific aspect of C++ and related concepts.

## Directory Structure

### [basics/](basics/README.md)

Core C++ language features and fundamentals:

- Variables, types, and type casting
- References and pointers
- Object-oriented programming (classes, inheritance, virtual functions)
- Memory management and allocators
- Exception handling
- Type information (typeid, decltype)
- Modern C++ features (constexpr, in_place, variant)

### [templates/](templates/README.md)

Template metaprogramming and advanced type manipulation:

- Template type deduction rules
- Template template parameters
- Fold expressions
- Function templates
- Type lists and metaprogramming techniques

### [stl/](stl/README.md)

Standard Template Library:

- **Containers**: vector, list, map, set, queue, deque, etc.
- **Algorithms**: sorting, searching, transformations, and more
- **Iterators**: iterator patterns and concepts
- **Functional**: function objects, lambdas, and functional programming
- **String**: string manipulation and algorithms
- **Random**: random number generation

### [threading/](threading/README.md)

Concurrency and multi-threading:

- Basic thread creation and management
- Synchronization primitives (mutexes, locks, condition variables)
- Packaged tasks and futures
- Thread-safe data structures
- Event handling and synchronization patterns
- Concurrent programming patterns

### [idioms/](idioms/README.md)

C++ design patterns and idioms:

- CRTP (Curiously Recurring Template Pattern)
- Modern C++ idioms and best practices
- Design patterns adapted for C++

### [experiment/](experiment/README.md)

Experimental code and standalone examples:

- Various experimental implementations
- One-off examples and proof-of-concepts
- Educational implementations

### [advanced/](advanced/README.md)

Advanced C++ concepts:

- Complex template patterns
- Advanced memory management techniques
- Optimization strategies
- Platform-specific code

## Getting Started

1. Start with [basics/](basics/README.md) if you're new to C++
2. Progress through [templates/](templates/README.md) for advanced type manipulation
3. Explore [stl/](stl/README.md) for standard library usage
4. Learn concurrency with [threading/](threading/README.md)
5. Study [idioms/](idioms/README.md) for best practices
6. Check [experiment/](experiment/README.md) for experimental code
7. Dive into [advanced/](advanced/README.md) for complex topics

## Building and Running

To compile any file in these directories:

```bash
g++ -std=c++17 -o output source.cpp
```

Or use the VS Code build task:

- Press `Ctrl+Shift+B` to build the active file

## Related Directories

- [Header files and utilities](../include/README.md) - Reusable headers and utilities
- [Main project README](../README.md) - Project overview and resources

---

**Back to**: [Main README](../README.md)

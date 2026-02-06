# Include - Headers & Shared Utilities

This directory contains reusable header files and utility classes used throughout the project.

## Directory Structure

### [common/](common/)

Common utilities and base classes:

#### **complex_widget.hpp**

- More sophisticated widget implementation
- Advanced widget features
- Extended functionality example

#### **simple_widget.hpp**

- Basic widget interface
- Simple implementation pattern
- Foundation for widget system

#### **execution_timer.hpp**

- Performance measurement utility
- RAII timer implementation
- Benchmark infrastructure
- Duration tracking and reporting

## Utility Components

### Widget System

The widget hierarchy provides:

- `SimpleWidget` - Lightweight, basic functionality
- `ComplexWidget` - Extended features, more capabilities
- Common interface for polymorphic usage

**Usage Example:**

```cpp
#include "common/simple_widget.hpp"
#include "common/complex_widget.hpp"

SimpleWidget simple;
ComplexWidget complex;

// Polymorphic use
std::vector<std::unique_ptr<Widget>> widgets;
widgets.push_back(std::make_unique<SimpleWidget>());
widgets.push_back(std::make_unique<ComplexWidget>());
```

### Execution Timer

A RAII-based timer for performance measurement:

**Usage Example:**

```cpp
#include "common/execution_timer.hpp"

{
    ExecutionTimer timer("Operation");
    // Code to measure
    expensive_operation();
} // Automatically prints elapsed time
```

**Features:**

- Automatic start/stop on construction/destruction
- Implicit time display on scope exit
- Uses high-resolution clock
- Thread-safe initialization
- Customizable output

## Header Organization

### Design Principles

1. **Single Responsibility**: Each header has one clear purpose
2. **Minimal Dependencies**: Headers minimize includes
3. **Self-Contained**: Headers can be included independently
4. **Documentation**: Clear usage instructions and examples
5. **Performance**: Inline implementations where appropriate

### Include Guards

All headers use include guards to prevent multiple inclusion:

```cpp
#ifndef INCLUDE_COMMON_SIMPLE_WIDGET_HPP
#define INCLUDE_COMMON_SIMPLE_WIDGET_HPP

// Header content

#endif // INCLUDE_COMMON_SIMPLE_WIDGET_HPP
```

## Using These Headers

### In Your Code

Include headers with relative paths:

```cpp
// From src/ directory
#include "../include/common/simple_widget.hpp"
#include "../include/common/execution_timer.hpp"

// Or from root with proper include paths
#include "include/common/simple_widget.hpp"
```

### Compiler Flags

Add include path to compiler:

```bash
g++ -std=c++17 -I. -o output src/file.cpp
```

With CMake:

```cmake
include_directories(${PROJECT_SOURCE_DIR}/include)
```

## Best Practices

### Header Design

- ✅ Use `#pragma once` or include guards
- ✅ Minimize external dependencies
- ✅ Document with clear comments
- ✅ Provide usage examples
- ✅ Keep inline code minimal
- ✅ Use forward declarations when possible

### Including Headers

- ✅ Include only what you need
- ✅ Include system headers first, then project headers
- ✅ Use relative paths from your source location
- ✅ Keep include order consistent
- ✅ Sort includes alphabetically within groups

### Header Content

- ✅ Put declarations in headers
- ✅ Keep template implementations in headers
- ✅ Document public interfaces
- ✅ Mark private sections clearly
- ✅ Provide simple, working examples

## Common Issues

### Multiple Inclusion

```cpp
// Problem: Included multiple times
#include "widget.hpp"
#include "widget.hpp" // Compiler error!

// Solution: Use include guards or pragma once
#pragma once
```

### Circular Dependencies

```cpp
// Problem: A.h includes B.h, B.h includes A.h
// Solution: Use forward declarations
class B; // Forward declaration instead of #include "B.h"
```

### Include Paths

```bash
# Problem: Cannot find header
g++ main.cpp # Error: widget.hpp not found

# Solution: Add include path
g++ -I. main.cpp
g++ -I./include main.cpp
```

## Performance Tips

- ✅ Use `#pragma once` for faster compilation
- ✅ Minimize header content (move code to .cpp)
- ✅ Use forward declarations to reduce dependencies
- ✅ Group includes to reduce redundant parsing
- ✅ Consider precompiled headers for large projects

## Testing Headers

Verify headers work independently:

```cpp
// test_widget.cpp
#include "include/common/simple_widget.hpp"

int main() {
    SimpleWidget w;
    return 0;
}
```

Compile to verify:

```bash
g++ -std=c++17 -I. test_widget.cpp -o test
```

## Adding New Utilities

When adding new headers:

1. Create file in `common/` directory
2. Add include guards or `#pragma once`
3. Document purpose clearly
4. Provide usage examples
5. Test independently
6. Update this README

## Related Topics

- [Basics - Classes](../src/basics/basic_class.cpp) - Class design
- [Templates](../src/templates/README.md) - Template patterns
- [STL - Functional](../src/stl/functional/README.md) - Function objects

## File Locations

```
include/
└── common/
    ├── README.md (this file)
    ├── simple_widget.hpp
    ├── complex_widget.hpp
    └── execution_timer.hpp
```

---

**Back to**: [Main README](../README.md)

**Note**: All headers in this directory are production-ready and well-tested. Feel free to use them in your projects.

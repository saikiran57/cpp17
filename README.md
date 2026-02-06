# C++17 Learning Project

A comprehensive C++ learning repository covering core language features, modern C++17 concepts, STL, templates, threading, and design patterns.

## Project Structure

```
cpp17/
├── src/                      # Source code organized by topic
│   ├── basics/              # Core C++ language features
│   ├── templates/           # Template metaprogramming
│   ├── stl/                 # Standard Template Library
│   ├── threading/           # Concurrency and threading
│   ├── idioms/              # C++ design patterns and idioms
│   ├── experiment/          # Experimental code and examples
│   └── advanced/            # Advanced C++ concepts
├── include/                  # Header files and utilities
├── build/                    # Build artifacts (generated)
├── external/                 # External dependencies (googletest, etc.)
└── tools/                    # Utility scripts and tools
```

## Directory Overview

### [src/](src/README.md) - Source Code

Main source code directory organized by topic:

- **[basics/](src/basics/README.md)** - Core C++ language features and fundamentals
- **[templates/](src/templates/README.md)** - Template metaprogramming and type deduction
- **[stl/](src/stl/README.md)** - Standard Template Library containers, algorithms, and utilities
- **[threading/](src/threading/README.md)** - Concurrency, mutexes, and thread synchronization
- **[idioms/](src/idioms/README.md)** - C++ design patterns and idioms (CRTP, etc.)
- **[experiment/](src/experiment/README.md)** - Experimental code and standalone examples
- **[advanced/](src/advanced/README.md)** - Advanced C++ concepts

### [include/](include/README.md) - Headers and Utilities

Reusable header files and utility classes:

- Common widget implementations
- Execution timing utilities
- Shared utilities

## Topics Covered

### Basics

- Variables, types, and casting
- References and pointers
- Object-oriented programming (classes, inheritance, virtual functions)
- Memory management and allocators
- Exception handling
- Type identification (typeid, decltype)
- Modern C++ features (constexpr, in_place, variant)

### Templates

- Template type deduction
- Template template parameters
- Template keyword usage
- Fold expressions
- Function templates
- Type lists and metaprogramming

### Standard Template Library (STL)

- **Containers**: vector, list, map, set, queue, etc.
- **Algorithms**: sorting, searching, transformations
- **Iterators**: iterator concepts and usage
- **Functional Programming**: function objects, lambda expressions
- **String Manipulation**: string algorithms and utilities
- **Random Number Generation**

### Threading & Concurrency

- Basic threading
- Synchronization primitives (mutexes, locks)
- Packaged tasks and futures
- Thread-safe data structures
- Event handling
- Concurrent patterns

### Design Patterns & Idioms

- CRTP (Curiously Recurring Template Pattern)
- Modern C++ idioms
- Best practices

## Getting Started

### Prerequisites

- C++17 compatible compiler (g++, clang)
- CMake (optional)
- GoogleTest for testing (external dependency)

### Building

Using the build task:

```bash
# Build the active file
g++-14 -fdiagnostics-color=always -g <file>.cpp -o <output>
```

Or manually:

```bash
g++ -std=c++17 -o output src/file.cpp
```

## Development Tools

### Code Formatting

Run all C++ files through clang-format:

```bash
./format_all_cpp_files.sh
```

### Pre-commit Hooks

This project uses pre-commit hooks for code quality:

```bash
# Install pre-commit
pip install pre-commit

# Install the git hooks
pre-commit install

# Run pre-commit on all files
pre-commit run --all-files
```

More info:

- https://pre-commit.com/
- https://medium.com/@0xmatriksh/how-to-setup-git-hooks-pre-commit-commit-msg-in-my-project-11aaec139536

## Resources

- [C++ STL Powerful Guide](https://leetcode.com/discuss/study-guide/4056690/C%2B%2B-STL-POWERFUL-GUIDE)
- C++17 Standard Reference
- Modern C++ Best Practices

## License

See [LICENSE](LICENSE) file for details.

---

**Note**: Each subdirectory has its own README with specific topics and examples. Start with the topic of interest or follow the learning path from basics to advanced.

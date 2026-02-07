# Experiment - Experimental Code & Examples

This directory contains experimental implementations, one-off examples, and proof-of-concepts. Code here is for learning and exploration purposes.

## Contents Overview

### Utilities & Helpers

- **execution_timer.hpp** - Performance measurement utility

  - Time duration measurements
  - Benchmark helper for code profiling
  - RAII timer implementation

- **byte_array.hpp** - Byte array implementation

  - Fixed-size byte container
  - Binary data handling
  - Memory representation utilities

- **byte_array_test.cpp** - Tests for byte_array implementation

### Algorithms & Utilities

- **cal_prime_numbers.cpp** - Prime number calculation

  - Sieve of Eratosthenes
  - Prime generation algorithms
  - Number theory examples

- **copy.cpp** - Copy semantics exploration

  - Deep vs. shallow copying
  - Copy constructor behavior
  - Assignment operator implementation

- **magic_conversion.cpp** - Type conversion tricks

  - Implicit conversions
  - User-defined conversion operators
  - Type coercion exploration

- **print_pattern.cpp** - Pattern printing examples
  - ASCII art generation
  - Loop-based pattern creation
  - String manipulation

### Data Structure & Algorithm Experiments

- **map_with_high_load.cpp** - Hash map performance under load

  - Collision handling
  - Load factor effects
  - Performance testing with large datasets

- **vsa.cpp** - Variable-sized array experiments

  - Dynamic array handling
  - Memory allocation strategies
  - Size-flexible containers

- **tbb.cpp** - Threading Building Blocks exploration
  - Parallel algorithms
  - Task-based parallelism
  - High-level threading abstractions

## Experimental Projects

### Code Organization

These files explore various approaches to solving problems and understanding C++ features. They may include:

- Working prototypes of algorithms
- Performance comparison implementations
- Educational examples
- Feature explorations
- Proof-of-concept code

### Purpose of This Directory

- **Learning**: Understand how things work internally
- **Testing**: Try new ideas and techniques
- **Benchmarking**: Performance measurement and comparison
- **Prototyping**: Quick implementation before finalization
- **Teaching**: Educational examples for specific concepts

## Using Experimental Code

### Building

Compile individual files with:

```bash
g++ -std=c++17 -o output filename.cpp
```

For threading support:

```bash
g++ -std=c++17 -pthread -o output filename.cpp
```

For optimization (benchmarking):

```bash
g++ -std=c++17 -O3 -o output filename.cpp
```

### Running

Execute the compiled binary:

```bash
./output
```

With arguments (if supported):

```bash
./output arg1 arg2 ...
```

## Code Quality Notes

⚠️ **Important**: Code in this directory may:

- Not follow all production standards
- Have limited error handling
- Include commented-out code
- Lack comprehensive documentation
- Not be fully optimized
- Be incomplete or abandoned

For production use, refer to:

- Finalized code in other directories
- Well-tested STL implementations
- Peer-reviewed, documented code

## Learning Examples

### Performance Measurement

The execution_timer utility demonstrates:

- RAII pattern for resource management
- Chrono library usage
- High-precision timing
- Benchmark infrastructure

### Custom Data Structures

Files like byte_array show:

- Template implementation
- Memory management
- Operator overloading
- Custom containers

### Algorithm Exploration

Examples like cal_prime_numbers explore:

- Classic algorithms
- Performance optimization
- Different approach comparisons
- Mathematical problem-solving

## Related Topics

- [Basics - Move Semantics](../basics/move.cpp) - Efficient transfer in copy.cpp
- [STL - Algorithms](../stl/algorithm/README.md) - Standard algorithms
- [STL - Containers](../stl/containers/README.md) - Container usage
- [Threading - Patterns](../threading/patterns/README.md) - Concurrent patterns in tbb.cpp

## Tips for Experimentation

- ✅ Test ideas quickly with simple examples
- ✅ Use execution_timer for performance comparison
- ✅ Document findings and conclusions
- ✅ Clean up and refactor successful experiments
- ✅ Move proven code to appropriate directories
- ✅ Remove or archive unsuccessful experiments

## File Naming Convention

- `*_test.cpp` - Tests for corresponding implementation
- `*.hpp` - Header file implementations
- `*.cpp` - Standalone executable examples
- Regular names - Primary experimental file

---

**Back to**: [Source Directory](../README.md) | [Main README](../../README.md)

**Note**: Some code in this directory may still be under development. Use with understanding that quality and completeness may vary.

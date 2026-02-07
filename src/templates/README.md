# Templates - Template Metaprogramming & Type Deduction

This directory contains comprehensive examples of C++ template metaprogramming, type deduction rules, and advanced template techniques.

## Contents Overview

### Template Fundamentals

- **template_type_deduction.cpp** - How C++ deduces template types

  - Type deduction for function templates
  - Type deduction rules and special cases
  - Universal references and perfect forwarding

- **template_template.cpp** - Templates that take templates as parameters

  - Generic algorithms on container types
  - Higher-order template programming

- **template_keyword.cpp** - Proper use of the `template` keyword
  - Disambiguating template syntax
  - Dependent name resolution

### Advanced Techniques

- **type_list.cpp** - Type list manipulation

  - Compile-time container for types
  - Type list algorithms
  - Variadic templates

- **widges.cpp** - Widget-based template examples
  - Generic widget patterns
  - Template specialization

### Fold Expressions

- **fold/** - Subdirectory with fold expression examples
  - Left and right folds
  - Binary operators with variadic templates
  - Recursive template elimination

### Function Templates

- **function/** - Subdirectory with function template examples
  - Generic function implementations
  - Specialization strategies
  - SFINAE (Substitution Failure Is Not An Error)

## Key Concepts

### Type Deduction Rules

Template type deduction follows specific rules:

1. **Non-reference parameter**: Template type is deduced from argument, ignoring reference/const
2. **Reference parameter**: Both template type and argument are deduced considering references
3. **Pointer parameter**: Template type excludes pointer, deduced from pointee
4. **Universal reference**: Special handling for perfect forwarding

### Template Specialization

- **Implicit instantiation**: Compiler generates code when needed
- **Explicit instantiation**: Manual template code generation
- **Specialization**: Provide specific implementation for certain types

### Variadic Templates

- Accept variable number of template parameters
- Process parameters recursively or with fold expressions
- C++17 fold expressions simplify variadic logic

### SFINAE

- **Substitution Failure Is Not An Error**
- Failed template specialization is not an error
- Enables compile-time function overloading based on type traits

## Common Patterns

### Perfect Forwarding

```cpp
template<typename T>
void forward_function(T&& arg) {
    other_function(std::forward<T>(arg));
}
```

Preserves lvalue/rvalue nature of arguments through forwarding.

### Type Traits

Query and modify type information at compile time:

- `std::is_const<T>`
- `std::is_pointer<T>`
- `std::enable_if<condition>`

### Compile-Time Computation

- Use constexpr functions for algorithms
- Use type lists for meta-computations
- Fold expressions for variadic reduction

## Building Examples

Compile any file with:

```bash
g++ -std=c++17 -o output filename.cpp
```

With verbose template error messages:

```bash
g++ -std=c++17 -ftemplate-backtrace-limit=0 -o output filename.cpp
```

## Learning Path

1. Start with **template_type_deduction.cpp** - Understand type deduction
2. Learn **function/basic_template.cpp** - Basic function templates
3. Study **template_template.cpp** - Advanced pattern
4. Explore **type_list.cpp** - Metaprogramming foundations
5. Master **fold/** - Modern C++17 approach
6. Review **template_keyword.cpp** - Syntax nuances

## Related Topics

- [Basics - constexpr](../basics/constexpr.cpp) - Compile-time computation
- [STL - Functional](../stl/functional/README.md) - Function objects and traits
- [STL - Containers](../stl/containers/README.md) - Generic container usage

## Tips & Tricks

- ✅ Use `std::forward<T>()` with universal references for perfect forwarding
- ✅ Use `auto` for template type deduction in C++17 and later
- ✅ Use `if constexpr` for compile-time branching (C++17)
- ✅ Use concepts for template constraints (C++20)
- ✅ Understand deduction guides for template instantiation (C++17)
- ✅ Use fold expressions instead of recursive template instantiation

## Common Pitfalls

1. **Type deduction confusion**: Non-reference parameters lose const/reference qualifiers
2. **Dependent names**: Use `typename` and `template` keywords for dependent types
3. **Template bloat**: Explicit instantiation can reduce binary size
4. **Compiler errors**: Template errors can be cryptic; use verbose flags
5. **Two-phase lookup**: Names in templates may behave unexpectedly

## Compiler Flags

```bash
# Verbose template diagnostics
g++ -std=c++17 -ftemplate-backtrace-limit=0

# Show instantiation information
g++ -std=c++17 -fdiagnostics-show-template-tree

# Generate template usage report
g++ -std=c++17 -save-temps
```

---

**Back to**: [Source Directory](../README.md) | [Main README](../../README.md)

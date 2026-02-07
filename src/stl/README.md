# STL - Standard Template Library

This directory contains comprehensive examples of the C++ Standard Template Library, covering containers, algorithms, iterators, and utility components.

## Directory Structure

### [containers/](containers/README.md)

Container data structures:

- **Sequential**: vector, deque, list, forward_list
- **Associative**: map, multimap, set, multiset
- **Unordered**: unordered_map, unordered_set
- **Adapters**: queue, priority_queue, stack
- Container selection and usage patterns

### [algorithm/](algorithm/README.md)

Algorithms for data manipulation:

- **Searching**: find, search, binary_search, lower_bound, upper_bound
- **Sorting**: sort, stable_sort, partial_sort, nth_element
- **Transformations**: transform, copy, rotate, reverse
- **Partitioning**: partition, stable_partition
- **Numeric**: accumulate, inner_product, partial_sum
- **Set operations**: set_union, set_intersection, set_difference
- **Min/Max**: min, max, min_element, max_element

### [iterators/](iterators/README.md)

Iterator patterns and concepts:

- **Iterator categories**: input, output, forward, bidirectional, random access
- **Iterator adapters**: reverse_iterator, insert_iterator
- **Streams as iterators**: istream_iterator, ostream_iterator
- **Iterator utilities**: distance, advance, next, prev

### [functional/](functional/README.md)

Function objects and functional programming:

- **Function objects**: std::function, std::bind
- **Lambda expressions**: capture modes, mutable lambdas
- **Comparators**: custom comparison for sorting and searching
- **Predicates**: unary and binary predicates for algorithms
- **Allocators**: custom memory allocation strategies

### [string/](string/README.md)

String manipulation and processing:

- **std::string**: basic string operations
- **String views**: std::string_view for non-owning references
- **String algorithms**: searching, replacing, trimming
- **Regular expressions**: pattern matching (C++11)
- **Conversion**: string to number conversions

### [random/](random/README.md)

Random number generation:

- **Engines**: mersenne_twister_engine, linear_congruential_engine
- **Distributions**: uniform, normal, poisson, exponential
- **Random device**: seed generation
- **Best practices**: seeding and state management

### [references/](references/README.md)

Reference implementations and example usage:

- Common usage patterns
- Cookbook recipes
- Performance considerations

### [general/](general/README.md)

General utilities and miscellaneous:

- **Pair and tuple**: heterogeneous collections
- **Optional**: optional values (C++17)
- **Variant**: type-safe unions (C++17)
- **Any**: type-erased values (C++17)
- **Bitset**: fixed-size bit sequences

## Key Concepts

### Container Selection

Choose the right container based on your needs:

| Container     | Insert   | Delete   | Lookup   | Iteration |
| ------------- | -------- | -------- | -------- | --------- |
| vector        | O(n)     | O(n)     | O(n)     | O(1)      |
| deque         | O(n)     | O(n)     | O(n)     | O(1)      |
| list          | O(1)     | O(1)     | O(n)     | O(1)      |
| map           | O(log n) | O(log n) | O(log n) | O(n)      |
| unordered_map | O(1) avg | O(1) avg | O(1) avg | O(n)      |

### Algorithm Complexity

- Most algorithms are O(n log n) for sorting
- Linear algorithms: O(n)
- Binary search: O(log n)
- Set operations: O(n + m)

### Iterator Requirements

Different algorithms have different iterator requirements:

- **Sequential access**: any iterator
- **Random access**: algorithms like binary_search need random-access iterators
- **Mutable access**: algorithms like sort need mutable iterators

## Building Examples

Compile any file with:

```bash
g++ -std=c++17 -o output filename.cpp
```

For optimized code:

```bash
g++ -std=c++17 -O2 -o output filename.cpp
```

## Learning Path

1. **Start with containers**: Understand vector, list, map
2. **Learn algorithms**: How to use sort, find, transform
3. **Master iterators**: Understand iterator concepts and categories
4. **Functional programming**: Lambdas, comparators, predicates
5. **String operations**: String manipulation patterns
6. **Random numbers**: Proper random generation and seeding
7. **Advanced utilities**: Optional, variant, any

## Common Patterns

### Range-based Processing

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
for(auto& elem : v) {
    process(elem);
}
```

### Lambda with Algorithm

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
std::sort(v.begin(), v.end(),
    [](int a, int b) { return a > b; });
```

### Chaining Operations

```cpp
std::vector<int> result;
std::copy_if(input.begin(), input.end(),
    std::back_inserter(result),
    [](int x) { return x > 0; });
```

## Performance Tips

- ✅ Reserve space in vectors before inserting: `v.reserve(n)`
- ✅ Use move semantics: `std::move()` for transfers
- ✅ Choose correct container for your access pattern
- ✅ Use `std::unordered_map` for O(1) lookup (when hash is good)
- ✅ Use algorithms instead of manual loops for compiler optimizations
- ✅ Use `std::string_view` to avoid copies
- ✅ Batch operations when possible

## Common Pitfalls

1. **Iterator invalidation**: Modifying container invalidates iterators
2. **Comparing unordered containers**: No defined equality
3. **Empty container access**: Undefined behavior on empty containers
4. **String copies**: Avoid unnecessary string allocations
5. **Reference lifetime**: Iterator/reference references must outlive use
6. **Comparison function consistency**: Comparators must define strict weak ordering

## Best Practices

- ✅ Use STL algorithms instead of manual loops
- ✅ Use `const` iterators for read-only access
- ✅ Use `std::find` instead of manual search loops
- ✅ Use `std::any_of`, `std::all_of` for predicates
- ✅ Prefer `std::unique_ptr` over raw pointers in containers
- ✅ Use `std::make_tuple` and structured bindings (C++17)

## Related Topics

- [Basics - Lambda](../basics/lambda.cpp) - Lambda expression syntax
- [Templates - Functional](../templates/function/README.md) - Template patterns with functions
- [STL - Modern Utilities](general/README.md) - C++17 utilities

---

**Back to**: [Source Directory](../README.md) | [Main README](../../README.md)

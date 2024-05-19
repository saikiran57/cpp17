#include <type_traits> // std::is_fundamental
#include <vector>
#include <iostream>
#include <chrono>

template <typename T> class no_init {
  static_assert(std::is_fundamental<T>::value, "should be a fundamental type");

public:
  // constructor without initialization
  no_init() noexcept {}
  // implicit conversion T → no_init<T>
  constexpr no_init(T value) noexcept : v_{value} {}
  // implicit conversion no_init<T> → T
  constexpr operator T() const noexcept { return v_; }

private:
  T v_;
};

int main() {
  auto begin = std::chrono::system_clock::now();
  {
  std::vector<no_init<int>> v;
  v.resize(2'000'000'000); // fast - no init!
  v[1024] = 47;
  int j = v[1024];
  v.push_back(23);
  }
  auto end = std::chrono::system_clock::now();

  std::cout << "duration ms: " << std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count() << "\n";
}
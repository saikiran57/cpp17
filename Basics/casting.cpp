#include <iostream>

class Book {
public:
  Book(int a) : val(a) {}
  constexpr auto len() const { return val; }

private:
  int val;
};

int main() {
  Book b(10);

  return 0;
}
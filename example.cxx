#include <iostream>
#include <random>
#include "statelessrnd.hpp"

template <typename T>
void print(T rnd) {
  std::cout << *rnd << '\n';
}

int main() {
  using namespace statelessrnd;

  constexpr minstd_rand rnd{42u};
  constexpr auto rnd2 = rnd.next();
  std::cout << *rnd << '\n';
  std::cout << *rnd2 << '\n';

  constexpr auto a = *rnd;
  constexpr auto b = rnd.value();
  constexpr decltype(rnd)::value_type c{rnd};
  static_assert(a == b && a == c);

  constexpr minstd_rand seed{42u, false};
  static_assert(*seed == 42u);

  constexpr auto rnd3 = seed.next().next().next();
  static_assert(minstd_rand{*rnd3}.value() == rnd3.next().value());

  auto stlrnd = std::minstd_rand(*seed);
  stlrnd.discard(100);
  std::cout << stlrnd() << '\n';
  std::cout << seed.discard(101).value() << '\n';

  std::cout << minstd_rand{stlrnd()}.value() << '\n';
  std::cout << stlrnd() << '\n';

  return 0;
}

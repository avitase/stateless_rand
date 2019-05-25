#include <iostream>
#include <random>
#include "statelessrnd.hpp"

int main() {
  using namespace statelessrnd;

  constexpr auto rnd = minstd_rand::seed(42u);
  constexpr auto rnd2 = rnd.next();
  std::cout << *rnd << '\n';
  std::cout << *rnd2 << '\n';

  constexpr auto a = *rnd;
  constexpr auto b = rnd.value();
  constexpr decltype(rnd)::value_type c{rnd};
  static_assert(a == b && a == c);

  constexpr auto seed = minstd_rand::seed(42u, false);
  static_assert(*seed == 42u);

  constexpr auto rnd3 = seed.next().next().next();
  static_assert(minstd_rand::seed(*rnd3).value() == rnd3.next().value());

  auto stlrnd = std::minstd_rand(*seed);
  stlrnd.discard(100);
  std::cout << stlrnd() << '\n';
  std::cout << seed.discard(101).value() << '\n';

  std::cout << minstd_rand::seed(stlrnd()).value() << '\n';
  std::cout << stlrnd() << '\n';

  return 0;
}

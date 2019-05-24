#include <catch.hpp>
#include <limits>
#include <random>
#include "statelessrnd.hpp"

template <bool b>
constexpr auto static_test() noexcept {
  static_assert(b);
  return b;
}

constexpr statelessrnd::minstd_rand::value_type default_seed = 42u;

TEST_CASE("Value does not change for subsequent calls to non-const getter",
          "[stateless_rnd]") {
  statelessrnd::minstd_rand rnd{default_seed};
  auto value = *rnd;
  REQUIRE(rnd.value() == value);
  REQUIRE(rnd.value() == value);
}

TEST_CASE("Getters return all same value after calling next() once",
          "[stateless_rnd]") {
  using namespace statelessrnd;
  constexpr auto rnd = minstd_rand{default_seed}.next();
  constexpr auto value = rnd.value();
  REQUIRE(static_test<rnd.value() == value>());
  REQUIRE(static_test<*rnd == value>());
  REQUIRE(static_test<static_cast<minstd_rand::value_type>(rnd) == value>());
}

TEST_CASE("Discard skips random numbers", "[stateless_rnd]") {
  constexpr statelessrnd::minstd_rand rnd{default_seed};
  constexpr auto next3 = rnd.next().next().next();
  REQUIRE(static_test<next3.value() == rnd.discard(3).value()>());
}

TEST_CASE("Random numbers match those of std::minstd_rand", "[stateless_rnd]") {
  constexpr statelessrnd::minstd_rand rnd1{default_seed};
  std::minstd_rand rnd2{default_seed};

  REQUIRE(rnd1.value() == rnd2());

  rnd2.discard(100);
  REQUIRE(rnd1.discard(101).value() == rnd2());

  rnd2.discard(1000);
  REQUIRE(rnd1.discard(1102).value() == rnd2());
}

TEST_CASE("min() and max() values match those of std::minstd_rand",
          "[stateless_rnd]") {
  constexpr statelessrnd::minstd_rand rnd1{default_seed};
  constexpr auto min = rnd1.min();
  constexpr auto max = rnd1.max();

  std::minstd_rand rnd2{default_seed};
  REQUIRE(min == rnd2.min());
  REQUIRE(max == rnd2.max());
}

TEST_CASE("When first value is not skipped, random number is seed",
          "[stateless_rnd]") {
  constexpr statelessrnd::minstd_rand rnd{default_seed, false};
  REQUIRE(static_test<rnd.value() == default_seed>());
}

TEST_CASE("Seeding enters a sequence", "[stateless_rnd]") {
  std::minstd_rand rnd1{default_seed};
  rnd1.discard(100);

  statelessrnd::minstd_rand rnd2{rnd1(), false};
  REQUIRE(rnd1() == rnd2.next().value());
}

TEST_CASE("Seed is clamped to [min(), max()]", "[stateless_rnd]") {
  using namespace statelessrnd;
  using seed_t = minstd_rand::value_type;
  constexpr seed_t invalid_seed1 = 0u;
  constexpr seed_t invalid_seed2 = std::numeric_limits<seed_t>::max();

  constexpr minstd_rand rnd1{invalid_seed1};
  constexpr minstd_rand rnd2{invalid_seed1};

  REQUIRE(static_test<rnd1.value() == minstd_rand{rnd1.min()}.value()>());
  REQUIRE(static_test<rnd2.value() == minstd_rand{rnd2.min()}.value()>());
}

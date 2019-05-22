#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <random>
#include "statelessrnd.hpp"

constexpr statelessrnd::stateless_rand::value_type default_seed = 42u;

TEST_CASE("Value does not change for subsequent calls to non-const getter",
          "[stateless_rnd]") {
  statelessrnd::stateless_rand rnd{default_seed};
  auto value = *rnd;
  REQUIRE(rnd.value() == value);
  REQUIRE(rnd.value() == value);
}

TEST_CASE("Getters return all same value after calling next() once",
          "[stateless_rnd]") {
  constexpr auto rnd = statelessrnd::stateless_rand{default_seed}.next();
  constexpr auto value = rnd.value();
  REQUIRE(rnd.value() == value);
  REQUIRE(*rnd == value);
  REQUIRE(static_cast<statelessrnd::stateless_rand::value_type>(rnd) == value);
}

TEST_CASE("Discard skips random numbers", "[stateless_rnd]") {
  constexpr statelessrnd::stateless_rand rnd{default_seed};
  REQUIRE(rnd.next().next().next().value() == rnd.discard(3).value());
}

TEST_CASE("Random numbers match those of std::minstd_rand", "[stateless_rnd]") {
  constexpr statelessrnd::stateless_rand rnd1{default_seed};
  std::minstd_rand rnd2{default_seed};

  REQUIRE(rnd1.value() == rnd2());

  rnd2.discard(100);
  REQUIRE(rnd1.discard(101).value() == rnd2());

  rnd2.discard(1000);
  REQUIRE(rnd1.discard(1102).value() == rnd2());
}
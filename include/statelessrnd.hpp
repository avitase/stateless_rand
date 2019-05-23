#pragma once

#include <cstdint>

namespace statelessrnd {
template <typename T, T A, T C, T M>
class stateless_rand final {
 public:
  using value_type = T;

 private:
  value_type _state;

  [[nodiscard]] static constexpr auto advance(value_type x) noexcept {
    return (x * A + C) % M;
  }

 public:
  constexpr explicit stateless_rand(value_type seed, bool skip_first = true)
      : _state(skip_first ? advance(seed) : seed) {}

  [[nodiscard]] constexpr auto next() const noexcept {
    return stateless_rand{_state, true};
  }

  [[nodiscard]] constexpr stateless_rand discard(unsigned int n) const
      noexcept {
    return (n == 0u ? stateless_rand{_state, false} : next().discard(n - 1));
  }

  [[nodiscard]] constexpr auto value() const noexcept { return _state; }

  [[nodiscard]] constexpr auto operator*() const noexcept { return value(); }

  [[nodiscard]] constexpr operator value_type() const noexcept {
    return value();
  }

  [[nodiscard]] constexpr auto min() const noexcept { return 1; }

  [[nodiscard]] constexpr auto max() const noexcept { return M - 1; }
};

using minstd_rand = stateless_rand<std::uint_fast32_t, 48271u, 0u, 2147483647u>;
}  // namespace statelessrnd

# `stateless_rand`

`stateless_rand` is a header-only, stateless (pseudo) random generator / number that implements the linear congruential relation `x <- (x * a + c) % m`, where `x` is the current state value, and `a`, `c` and `m` are referred to as multiplier, increment and modulus parameter, respectively. As all linear congruential algorithms, the generated (pseudo) random values suffer from the Marsaglia effect but benefit from the small state size and blazingly fast calculation. Always keep this in mind and use it wisely! (Especially, this library **should not be used for security relevant aspects** of your project!)

In marked difference to the implementation available within the STL, this implementation is purely functional and thus can be used in `constexpr` contexts without sacrificing functionality. The interface is kept as close as possible to the one provided by `std::linear_congruential_engine`. The most obvious difference is the `next()` method, which, instead of altering the internal state, returns a new instance of `stateless_rand` that represents the next value in the (pseudo) random sequence. Since the internal (constant) state has the size of an integer, this operation is efficient. It is impossible to change the internal state of the generator, it could hence also be considered a random number itself than a generator.

The state can be accessed via three equivalent methods: `*` (dereferencing operator), `value()` or the conversion operator to the underlying type. This underlying state type is a template parameter `T` but should in most cases set to `int`, `std::int32_t`, `std::int_fast32_t` or similar.

The sequence is seeded during construction. The first value (seed) is skipped by default, this can be changed though via setting `skip_first` to `false` (constructor parameter) during construction. Linear congruential algorithms produce fully deterministic sequences, seeding can therefore also be used as an entry point to a given sequence.

For the sake of compliance with `std::linear_congruential_engine`, we further provide getters for the minimum and maximum value of the sequence (`min()` and `max()`, respectively), as well as a mechanism to skip `n` values in the sequence via `discard(n)`. The latter is equivalent to `n` subsequent calls of `next()`. Note however, that the same might also be achieved by specifying a desired value of the sequence explicitly as a seed, which can be much faster, potentially.

The type of the state (accessible via `stateless_rand::value_type`), `a`, `c` and `m` are template parameters. A sensible choice which matches the one of `std::minstd_rand`, is named `minstd_rand` in the `statlessrnd` namespace of this library.

## Examples

We provide a variety of possible applications within our [test cases](test/test_stateless_rand.cpp). 

#pragma once

/// Helper implementation to pass multiple types around in a 'pack'
template <typename... Args>
struct arg_pack {};

using i8  = std::int8_t;
using u8  = std::uint8_t;
using i16 = std::int16_t;
using u16 = std::uint16_t;
using i32 = std::int32_t;
using u32 = std::uint32_t;
using i64 = std::int64_t;
using u64 = std::uint64_t;
// clang-format off


inline i8 operator"" _i8(unsigned long long int value) {
    return static_cast<i8>(value);
}

template <typename T> using R = T&;
template <typename T> using CR   = const T&;
template <typename T> using CP   = const T*;
template <typename T> using P    = T*;
template <typename T> using C    = const T;

template <typename T>
CR<T> cr(CR<T> in) {
   return in;
}

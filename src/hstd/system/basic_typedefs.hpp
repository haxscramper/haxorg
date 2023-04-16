#pragma once
#include <concepts>
#include <cstdint>
#include <QString>

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

inline u8 operator"" _u8(unsigned long long int value) {
    return static_cast<u8>(value);
}

inline QString operator"" _qs(const char* value, unsigned long size) {
    return QString(value);
}

template <typename T> using Ref   = T&;
template <typename T> using CR    = const T&;
template <typename T> using CP    = const T*;
template <typename T> using Ptr   = T*;
template <typename T> using Const = const T;
template <typename T> using Rw = std::reference_wrapper<T>;
template <typename T> using CRw = std::reference_wrapper<const T>;

template <typename T>
CR<T> cr(CR<T> in) {
   return in;
}

template<typename T, typename ... U>
concept IsAnyOf = (std::same_as<T, U> || ...);

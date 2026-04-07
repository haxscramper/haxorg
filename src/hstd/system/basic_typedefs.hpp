#pragma once
#include <concepts>
#include <cstdint>
#include <string>

namespace hstd {

/// Helper implementation to pass multiple types around in a 'pack'
template <typename... Args>
struct arg_pack {};

typedef int8_t             i8;
typedef unsigned char      u8;
typedef int16_t            i16;
typedef unsigned short     u16;
typedef int32_t            i32;
typedef unsigned int       u32;
typedef int64_t            i64;
typedef unsigned long long u64;
// clang-format off

static_assert(sizeof(u32) == 4, "Expected 4 bytes for u32");
static_assert(sizeof(u64) == 8, "Expected 8 bytes for u64");

inline i8 operator""_i8(unsigned long long int value) {
    return static_cast<i8>(value);
}

inline u8 operator""_u8(unsigned long long int value) {
    return static_cast<u8>(value);
}

inline std::string operator""_qs(const char* value, unsigned long size) {
    return std::string(value);
}

template <typename T> using Ref   = T&;
template <typename T> using CR    = const T&;
template <typename T> using CP    = const T*;
template <typename T> using Ptr   = T*;
template <typename T> using Const = const T;
template <typename T> using Rw = std::reference_wrapper<T>;
template <typename T> using CRw = std::reference_wrapper<const T>;

template <typename T>
T const& cr(T const& in) {
   return in;
}

template<typename T, typename ... U>
concept IsAnyOf = (std::same_as<T, U> || ...);

}

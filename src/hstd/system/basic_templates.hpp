#pragma once

#include <concepts>
#include <limits>
#include <algorithm>

#include <hstd/system/basic_typedefs.hpp>

/// \brief get next value
template <typename T>
T succ(T);

template <typename T>
concept ImplementsSucc = requires(CR<T> value) {
                             { succ(value) } -> std::same_as<T>;
                         };

/// \brief get previous value
template <typename T>
T prev(T);

template <typename T>
concept ImplementsPrev = requires(CR<T> value) {
                             { prev(value) } -> std::same_as<T>;
                         };

template <typename T>
T low();

template <typename T>
concept ImplementsLow = requires(CR<T> value) {
                            { low<T>() } -> std::same_as<T>;
                        };

template <typename T>
T high();

template <typename T>
concept ImplementsHigh = requires(CR<T> value) {
                             { high<T>() } -> std::same_as<T>;
                         };

template <typename T>
int ord(T val);

template <typename T>
concept ImplementsOrd = requires(CR<T> value) {
                            { ord(value) } -> std::same_as<int>;
                        };


template <typename T>
int ord(T value)
    requires(std::is_enum<T>::value)
{
    return static_cast<int>(value) - static_cast<int>(low<T>());
}

template <typename T>
T succ(T value)
    requires(std::is_enum<T>::value)
{
    return static_cast<T>(ord(value) + 1);
}

// clang-format off
template <> inline int succ(int val) { return val + 1; }
template <> inline char succ(char val) { return val + 1; }
template <> inline int ord(char c) { return static_cast<unsigned char>(c); }
template <> inline int ord(i8 c) { return static_cast<i8>(c); }

template <std::integral T> inline T low() { return std::numeric_limits<T>::min(); }
template <std::integral T> inline T high() { return std::numeric_limits<T>::max(); }

// clang-format on

template <std::integral T, std::integral Other>
T saturating_add(T value, Other change) {
    T res = value + change;
    // Can only happen due to overflow
    if (res < value) {
        res = high<T>();
    }
    return res;
}

template <std::integral T, std::integral Other>
T saturating_sub(T value, Other change) {
    T res = value - change;
    // Can only happen due to overflow
    if (value < res) {
        res = low<T>();
    }
    return res;
}

template <std::integral T, std::integral Other>
T saturating_add_any(T value, Other change) {
    if (0 <= change) {
        return saturating_add(value, change);
    } else {
        return saturating_sub(value, std::abs(change));
    }
}

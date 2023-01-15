#pragma once

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

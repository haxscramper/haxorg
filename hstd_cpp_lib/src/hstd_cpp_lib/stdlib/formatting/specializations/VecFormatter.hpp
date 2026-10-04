#pragma once

#include <hstd_cpp_lib/stdlib/containers/Vec.hpp>
#include <hstd_cpp_lib/stdlib/formatting/Formatter.hpp>

/// \brief Vector formatting operator
template <typename T>
struct fmt::formatter<hstd::Vec<T>>
    : hstd::std_item_iterator_formatter<T, hstd::Vec<T>> {};

template <typename T>
struct fmt::formatter<std::vector<T>>
    : hstd::std_item_iterator_formatter<T, std::vector<T>> {};

template <typename T, int Size>
struct fmt::formatter<hstd::SmallVec<T, Size>>
    : hstd::std_item_iterator_formatter<T, hstd::SmallVec<T, Size>> {};

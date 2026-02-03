#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Formatter.hpp>

/// \brief Vector formatting operator
template <typename T>
struct std::formatter<hstd::Vec<T>>
    : hstd::std_item_iterator_formatter<T, hstd::Vec<T>> {};

template <typename T>
struct std::formatter<std::vector<T>>
    : hstd::std_item_iterator_formatter<T, std::vector<T>> {};

template <typename T, int Size>
struct std::formatter<hstd::SmallVec<T, Size>>
    : hstd::std_item_iterator_formatter<T, hstd::SmallVec<T, Size>> {};

#pragma once

#include <hstd/stdlib/Formatter.hpp>
#include <hstd/stdlib/Vec.hpp>

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

template <typename T>
struct fmt::formatter<std::span<T>>
    : hstd::std_item_iterator_formatter<T, std::span<T>> {};

template <typename T>
struct fmt::formatter<hstd::Span<T>>
    : hstd::std_item_iterator_formatter<T, hstd::Span<T>> {};

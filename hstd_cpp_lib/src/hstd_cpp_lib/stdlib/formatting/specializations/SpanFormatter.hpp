#pragma once

#include <hstd_cpp_lib/stdlib/containers/Span.hpp>
#include <hstd_cpp_lib/stdlib/formatting/Formatter.hpp>

template <typename T>
struct fmt::formatter<hstd::Span<T>>
    : hstd::std_item_iterator_formatter<T, hstd::Span<T>> {};

template <typename T>
struct fmt::formatter<hstd::Span<const T>>
    : hstd::std_item_iterator_formatter<const T, hstd::Span<const T>> {};

template <typename T>
struct fmt::formatter<std::span<T>>
    : hstd::std_item_iterator_formatter<T, std::span<T>> {};

template <typename T>
struct fmt::formatter<std::span<const T>>
    : hstd::std_item_iterator_formatter<const T, std::span<const T>> {};

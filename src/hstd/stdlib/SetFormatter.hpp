#pragma once

#include <hstd/stdlib/Formatter.hpp>
#include <hstd/stdlib/Set.hpp>

template <typename T>
struct fmt::formatter<hstd::UnorderedSet<T>>
    : hstd::std_unordered_sequence_formatter<T, hstd::UnorderedSet<T>> {};

template <typename T>
struct fmt::formatter<std::unordered_set<T>>
    : hstd::std_unordered_sequence_formatter<T, std::unordered_set<T>> {};

template <typename T>
struct fmt::formatter<std::set<T>>
    : hstd::std_unordered_sequence_formatter<T, std::set<T>> {};

#pragma once

#include <hstd/stdlib/Set.hpp>
#include <hstd/stdlib/Formatter.hpp>

template <typename T>
struct std::formatter<hstd::UnorderedSet<T>>
    : hstd::std_unordered_sequence_formatter<T, hstd::UnorderedSet<T>> {};

template <typename T>
struct std::formatter<std::unordered_set<T>>
    : hstd::std_unordered_sequence_formatter<T, std::unordered_set<T>> {};

template <typename T>
struct std::formatter<std::set<T>>
    : hstd::std_unordered_sequence_formatter<T, std::set<T>> {};

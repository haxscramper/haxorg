#pragma once

#include <string>

/// \brief Format string to hex string padding it with leading zeroes based
/// on the type size
template <std::integral T>
std::string format_string_to_hex(T const& value);

extern template std::string format_string_to_hex<int>(int const& value);
extern template std::string format_string_to_hex<unsigned int>(
    unsigned int const& value);
extern template std::string format_string_to_hex<long int>(
    long int const& value);
extern template std::string format_string_to_hex<unsigned long int>(
    unsigned long int const& value);
extern template std::string format_string_to_hex<long long int>(
    long long int const& value);
extern template std::string format_string_to_hex<unsigned long long int>(
    unsigned long long int const& value);
extern template std::string format_string_to_hex<char>(char const& value);
extern template std::string format_string_to_hex<unsigned char>(
    unsigned char const& value);
extern template std::string format_string_to_hex<short int>(
    short int const& value);
extern template std::string format_string_to_hex<unsigned short int>(
    unsigned short int const& value);

template <std::integral T>
std::string format_string_to_bin(T const& value);

extern template std::string format_string_to_bin<int>(int const& value);
extern template std::string format_string_to_bin<unsigned int>(
    unsigned int const& value);
extern template std::string format_string_to_bin<long int>(
    long int const& value);
extern template std::string format_string_to_bin<unsigned long int>(
    unsigned long int const& value);
extern template std::string format_string_to_bin<long long int>(
    long long int const& value);
extern template std::string format_string_to_bin<unsigned long long int>(
    unsigned long long int const& value);
extern template std::string format_string_to_bin<char>(char const& value);
extern template std::string format_string_to_bin<unsigned char>(
    unsigned char const& value);
extern template std::string format_string_to_bin<short int>(
    short int const& value);
extern template std::string format_string_to_bin<unsigned short int>(
    unsigned short int const& value);

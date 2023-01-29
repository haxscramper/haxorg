#pragma once

#include <iostream>
#include <string>
#include <sstream>

#include <boost/mp11.hpp>
#include <boost/describe.hpp>

#ifdef __GNUG__
#    include <cstdlib>
#    include <memory>
#    include <cxxabi.h>

inline std::string demangle(const char* name) {

    int status = -4; // some arbitrary value to eliminate the compiler
                     // warning

    // enable c++11 by passing the flag -std=c++11 to g++
    std::unique_ptr<char, void (*)(void*)> res{
        abi::__cxa_demangle(name, NULL, NULL, &status), std::free};

    return (status == 0) ? res.get() : name;
}

#else

// does nothing if not g++
inline std::string demangle(const char* name) { return name; }

#endif


template <typename T>
concept StringStreamable = requires(T value, std::ostream& os) {
                               {
                                   os << value
                                   } -> std::same_as<std::ostream&>;
                           };

template <typename T>
std::string to_string(CR<T> value)
    requires StringStreamable<T>
{
    std::stringstream os;
    os << value;
    return os.str();
}

template <typename T>
concept StringConvertible = requires(T value) {
                                {
                                    to_string(value)
                                    } -> std::same_as<std::string>;
                            };

template <typename T>
concept IsEnum = std::is_enum<T>::value;

template <typename T>
concept DescribedEnum = IsEnum<T>
                     && boost::describe::has_describe_enumerators<
                            T>::value;

template <IsEnum T>
std::ostream& operator<<(std::ostream& os, T value) {
    return os << std::to_string((int)value);
}

template <DescribedEnum T>
std::ostream& operator<<(std::ostream& os, T value) {
    return os << boost::describe::enum_to_string(value, "<unnamed>");
}


/// \brief Escape string literal, converting newline and other (TODO)
/// control characters into unicode.
inline std::string escape_literal(std::string const& in) {
    std::string res;
    res.reserve(in.size() + 2);
    res += "«";
    for (char c : in) {
        if (c == '\n') {
            res += "␤";

        } else {
            res += c;
        }
    }

    res += "»";

    return res;
}

inline std::string right_aligned(
    CR<std::string> str,
    int             n,
    char            c = ' ') {
    std::string res;
    if (str.size() < n) {
        res.append(n - str.size(), c);
    }
    res.append(str);
    return res;
}

inline std::string left_aligned(CR<std::string> str, int n, char c = ' ') {
    auto s = str;
    if (s.size() < n) {
        s.append(n - s.size(), c);
    }
    return s;
}

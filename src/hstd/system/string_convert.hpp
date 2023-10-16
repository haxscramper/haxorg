#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <string>
#include <iostream>
#include <format>
#include <sstream>

#include <boost/mp11.hpp>
#include <boost/describe.hpp>

#include <locale>
#include <codecvt>

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
    { os << value } -> std::same_as<std::ostream&>;
};

template <typename T>
std::string to_string(T const& value)
    requires StringStreamable<T>
{
    std::string  out;
    std::ostream os{&out};
    os << value;
    return out;
}

inline std::string to_string(bool b) { return b ? "true" : "false"; }

template <typename T>
concept StringConvertible = requires(T value) {
    { to_string(value) } -> std::same_as<std::string>;
};


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

template <typename Iterable>
std::ostream& join(
    std::ostream&      os,
    std::string const& sep,
    Iterable const&    list) {
    int index = 0;
    for (const auto& it : list) {
        if (0 < index) {
            os << sep;
        }
        os << to_string(it);
        ++index;
    }
    return os;
}

template <typename Iterable>
std::string join(std::string const& sep, Iterable const& list) {
    std::string  out;
    std::ostream os{&out};
    std::string  join(os, sep, list);
    return out;
}

/// \brief Small insanity to allow for `os << "[" << join(os, "", "wer")
/// <<` and other stuff without having to break everything into multiple
/// lines. Yes, this overload makes zero sense but whatever.
inline std::ostream& operator<<(
    std::ostream&       os,
    std::ostream const& value) {
    return os;
}


#define __xxloc() std::cout << __FILE__ << ":" << __LINE__ << "\n";

extern std::ostream qcout;

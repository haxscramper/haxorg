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
#include <format>

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
std::string join(std::string const& sep, Iterable const& list) {
    std::string os;
    int         index = 0;
    for (const auto& it : list) {
        if (0 < index) { os += sep; }
        os += std::format("{}", it);
        ++index;
    }
    return os;
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

template <typename T>
concept StdFormattable = requires(T& v, std::format_context ctx) {
    std::formatter<std::remove_cvref_t<T>>().format(v, ctx);
};

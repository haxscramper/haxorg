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

inline std::string to_string(wchar_t wc) {
    std::string mb(MB_CUR_MAX, '\0');
    const int   ret = std::wctomb(&mb[0], wc);
    return std::string(&mb[0], ret);
}

template <typename Iterable>
std::ostream& join(std::ostream& os, CR<std::string> sep, Iterable list) {
    int index = 0;
    for (const auto& it : list) {
        if (0 < index) {
            os << sep;
        }
        os << it;
        ++index;
    }
    return os;
}

template <typename Iterable>
std::string join(CR<std::string> sep, Iterable list) {
    std::stringstream os;
    join(os, sep, list);
    return os.str();
}

/// \brief Small insanity to allow for `os << "[" << join(os, "", "wer")
/// <<` and other stuff without having to break everything into multiple
/// lines. Yes, this overload makes zero sense but whatever.
inline std::ostream& operator<<(
    std::ostream&       os,
    std::ostream const& value) {
    return os;
}

#pragma once

#include <iostream>
#include <string>
#include <format>
#include <boost/mp11.hpp>
#include <boost/describe.hpp>


namespace hstd {

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

} // namespace hstd

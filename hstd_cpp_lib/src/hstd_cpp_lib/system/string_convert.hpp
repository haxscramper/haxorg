#pragma once

#include <boost/describe.hpp>
#include <boost/mp11.hpp>
#include <fmt/format.h>
#include <iostream>
#include <string>

namespace hstd {

template <typename Iterable>
std::string join(std::string_view sep, Iterable const& list) {
    std::string os;
    int         index = 0;
    for (const auto& it : list) {
        if (0 < index) { os += sep; }
        os += fmt::format("{}", it);
        ++index;
    }
    return os;
}

template <typename Iterable>
[[deprecated("Use join with string literal argument")]] std::string join(
    char const*     sep,
    Iterable const& list) {
    return join(std::string_view{sep}, list);
}

/// \brief Small insanity to allow for `os << "[" << join(os, "", "wer")
/// <<` and other stuff without having to break everything into multiple
/// lines. Yes, this overload makes zero sense but whatever.
inline std::ostream& operator<<(std::ostream& os, std::ostream const&) { return os; }


#define __xxloc() std::cout << __FILE__ << ":" << __LINE__ << "\n";

template <typename T>
concept StdFormattable = fmt::is_formattable<std::remove_cvref_t<T>, char>::value;


} // namespace hstd

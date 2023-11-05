#pragma once

#include <format>

template <typename T, typename CharT>
using Fmt = std::formatter<T, CharT>;

template <typename T>
void with_std_formatter(T const& value) {
    if (false) {
        std::format_context*     ctx;
        std::formatter<T> const* fmt;
        auto                     result = fmt->format(value, *ctx);
        static_assert(std::is_same_v<
                      decltype(result),
                      std::format_context::iterator>);
    }
}

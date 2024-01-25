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

template <typename... _Args>
[[nodiscard]] inline std::string fmt(
    std::format_string<_Args...> __fmt,
    _Args&&... __args) {
    return std::vformat(__fmt.get(), std::make_format_args(__args...));
}

template <typename T>
std::string fmt1(T const& t) {
    with_std_formatter(t);
    return std::format("{}", t);
}

template <typename T, typename FormatContext>
FormatContext::iterator fmt_ctx(T const& t, FormatContext& ctx) {
    with_std_formatter(t);
    return std::formatter<T>{}.format(t, ctx);
}


template <typename FormatContext>
FormatContext::iterator fmt_ctx(const char* t, FormatContext& ctx) {
    with_std_formatter(t);
    return std::formatter<std::string>{}.format(t, ctx);
}


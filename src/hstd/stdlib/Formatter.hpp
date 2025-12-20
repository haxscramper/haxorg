#pragma once

#include <format>
#include <hstd/system/reflection.hpp>
#include <hstd/system/string_convert.hpp>

namespace hstd {


template <typename T, typename CharT>
using Fmt = ::std::formatter<T, CharT>;

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

template <hstd::StdFormattable T>
std::string fmt1_maybe(T const& t) {
    return std::format("{}", t);
}

template <typename T>
std::string fmt1_maybe(T const& t) {
    return std::format(
        "[not formattable {}]", hstd::value_metadata<T>::typeName());
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

template <typename T>
struct std_format_ptr_as_value : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(T const* p, FormatContext& ctx) const {
        if (p == nullptr) {
            return fmt_ctx("nullptr", ctx);
        } else {
            return fmt_ctx(*p, ctx);
        }
    }
};


template <typename T>
struct std_format_ptr_as_hex : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(T const* p, FormatContext& ctx) const {
        if (p == nullptr) {
            return fmt_ctx("nullptr", ctx);
        } else {
            return fmt_ctx(
                std::format("{:p}", static_cast<const void*>(p)), ctx);
        }
    }
};

template <typename T>
struct std_format_ptr_as_hex_and_value : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(T const* p, FormatContext& ctx) const {
        if (p == nullptr) {
            return fmt_ctx("nullptr", ctx);
        } else {
            fmt_ctx(
                std::format("{:p}->", static_cast<const void*>(p)), ctx);
            return fmt_ctx(*p, ctx);
        }
    }
};

template <typename T, typename Container>
struct std_item_iterator_formatter : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(Container const& p, FormatContext& ctx)
        const {
        fmt_ctx("[", ctx);
        bool first = true;
        for (const auto& value : p) {
            if (!first) { fmt_ctx(", ", ctx); }
            first = false;
            fmt_ctx(value, ctx);
        }
        return fmt_ctx("]", ctx);
    }
};

template <typename K, typename V, typename Type>
struct std_kv_tuple_iterator_formatter : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(Type const& p, FormatContext& ctx)
        const {
        fmt_ctx("{", ctx);
        bool first = true;
        for (const auto& [key, value] : p) {
            if (!first) { fmt_ctx(", ", ctx); }
            first = false;
            fmt_ctx(key, ctx);
            fmt_ctx(": ", ctx);
            fmt_ctx(value, ctx);
        }
        return fmt_ctx("}", ctx);
    }
};

} // namespace hstd

template <>
struct std::formatter<int const*> : hstd::std_format_ptr_as_value<int> {};

template <>
struct std::formatter<int*> : hstd::std_format_ptr_as_value<int> {};

template <typename T>
struct std::formatter<std::reference_wrapper<T>>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const std::reference_wrapper<T>& p, FormatContext& ctx)
        const {
        return fmt_ctx(p.get(), ctx);
    }
};

template <hstd::DescribedRecord R>
struct std::formatter<R> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(R const& p, FormatContext& ctx) const {
        bool first = true;
        ::hstd::fmt_ctx("{", ctx);
        ::hstd::for_each_field_value_with_bases(
            p, [&](char const* name, auto const& value) {
                if (!first) { ::hstd::fmt_ctx(", ", ctx); }
                ::hstd::fmt_ctx(".", ctx);
                ::hstd::fmt_ctx(name, ctx);
                ::hstd::fmt_ctx(" = ", ctx);
                ::hstd::fmt_ctx(value, ctx);
                first = false;
            });
        return ::hstd::fmt_ctx("}", ctx);
    }
};

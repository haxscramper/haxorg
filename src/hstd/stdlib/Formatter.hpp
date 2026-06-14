#pragma once

#include <fmt/base.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <hstd/system/reflection.hpp>
#include <hstd/system/string_convert.hpp>

namespace hstd {


template <typename T, typename CharT>
using Fmt = ::fmt::formatter<T, CharT>;

using fmt_iter = fmt::format_context::iterator;

/// \brief Early-fail the instantiation if the formatter is
/// invalid. This function is a no-op at runtime and serves only for the
/// developer's sanity to make the formatter failures more apparent.
template <typename T>
void with_std_formatter(T const& value) {
    static_assert(fmt::is_formattable<T>::value);
    // if (false) {
    //     fmt::format_context*     ctx;
    //     fmt::formatter<T> const* fmt;
    //     auto                     result = fmt->format(value, *ctx);
    //     static_assert(std::is_same_v<decltype(result), fmt::format_context::iterator>);
    // }
}

template <typename... Args>
[[nodiscard]] inline std::string fmt(fmt::format_string<Args...> format, Args&&... args) {
    return fmt::vformat(format.get(), fmt::make_format_args(args...));
}

template <typename T>
std::string fmt1(T const& t) {
    with_std_formatter(t);
    return fmt::format("{}", t);
}

template <hstd::StdFormattable T>
std::string fmt1_maybe(T const& t) {
    return fmt::format("{}", t);
}

template <typename T>
std::string fmt1_maybe([[maybe_unused]] T const& t) {
    return fmt::format("[not formattable {}]", hstd::value_metadata<T>::typeName());
}


template <typename T>
concept has_exact_pointer_formatter //
    = std::is_pointer_v<T> && requires(T const& value, fmt::format_context& ctx) {
          {
              fmt::formatter<T>{}.format(value, ctx)
          } -> std::same_as<fmt::format_context::iterator>;
      };

template <typename T>
fmt::format_context::iterator fmt_ctx(T const& t, fmt::format_context& ctx) {
    if constexpr (has_exact_pointer_formatter<T>) {
        fmt::formatter<T> formatter;
        return formatter.format(t, ctx);
    } else {
        with_std_formatter(t);
        return fmt::format_to(ctx.out(), "{}", t);
    }
}


fmt::format_context::iterator fmt_ctx(char const* t, fmt::format_context& ctx) {
    with_std_formatter(t);
    return fmt::format_to(ctx.out(), "{}", t);
}

template <typename T>
struct std_format_ptr_as_value {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    auto           format(T const* p, fmt::format_context& ctx) const {
        if (p == nullptr) {
            return fmt_ctx("nullptr", ctx);
        } else {
            return fmt_ctx(*p, ctx);
        }
    }
};


template <typename T>
struct std_format_ptr_as_hex {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    auto           format(T const* p, fmt::format_context& ctx) const {
        if (p == nullptr) {
            return fmt_ctx("nullptr", ctx);
        } else {
            return fmt_ctx(fmt::format("{:p}", static_cast<const void*>(p)), ctx);
        }
    }
};

template <typename T>
struct std_format_ptr_as_hex_and_value {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    auto           format(T const* p, fmt::format_context& ctx) const {
        if (p == nullptr) {
            return fmt_ctx("nullptr", ctx);
        } else {
            fmt_ctx(fmt::format("{:p}->", static_cast<const void*>(p)), ctx);
            return fmt_ctx(*p, ctx);
        }
    }
};

template <typename T, typename Container>
struct std_item_iterator_formatter {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    auto           format(Container const& p, fmt::format_context& ctx) const {
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
struct std_kv_tuple_iterator_formatter {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    auto           format(Type const& p, fmt::format_context& ctx) const {
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


template <typename T, typename Set>
struct std_unordered_sequence_formatter {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    auto           format(Set const& p, fmt::format_context& ctx) const {
        ::hstd::fmt_ctx("{", ctx);
        bool first = true;
        for (const auto& it : p) {
            if (!first) { hstd::fmt_ctx(", ", ctx); }
            first = false;
            hstd::fmt_ctx(it, ctx);
        }
        return hstd::fmt_ctx("}", ctx);
    }
};

template <typename T>
struct std_strong_typedef_formatter {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    auto           format(T const& p, fmt::format_context& ctx) const {
        hstd::fmt_ctx(hstd::value_metadata<T>::typeName(), ctx);
        hstd::fmt_ctx("(", ctx);
        hstd::fmt_ctx(p.t, ctx);
        return hstd::fmt_ctx(")", ctx);
    }
};

} // namespace hstd

template <>
struct fmt::formatter<int const*> : hstd::std_format_ptr_as_value<int> {};

template <>
struct fmt::formatter<int*> : hstd::std_format_ptr_as_value<int> {};

template <typename T>
struct fmt::formatter<std::reference_wrapper<T>> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(std::reference_wrapper<T> const& p, fmt::format_context& ctx)
        const {
        return fmt_ctx(p.get(), ctx);
    }
};

template <hstd::DescribedRecord R>
struct fmt::formatter<R> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    auto           format(R const& p, fmt::format_context& ctx) const {
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

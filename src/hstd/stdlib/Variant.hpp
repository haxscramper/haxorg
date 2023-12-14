#pragma once

#include <variant>
#include <hstd/system/string_convert.hpp>
#include <hstd/system/basic_templates.hpp>
#include <hstd/system/Formatter.hpp>

template <typename... Types>
using Variant = std::variant<Types...>;

// Type trait to check if a type is a specialization of std::variant
template <class T>
struct is_variant : std::false_type {};

template <class... Args>
struct is_variant<std::variant<Args...>> : std::true_type {};

// The concept uses the type trait after removing cv-ref qualifiers
template <typename T>
concept IsVariant = is_variant<std::remove_cvref_t<T>>::value;


template <IsVariant V>
struct std::formatter<V> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(const V& p, FormatContext& ctx) const {
        std::string res;
        fmt_ctx("Var(", ctx);
        fmt_ctx(p.index(), ctx);
        fmt_ctx(": ", ctx);
        std::visit([&ctx](const auto& value) { fmt_ctx(value, ctx); }, p);
        return fmt_ctx(")", ctx);
    }
};


template <IsVariant V>
auto variant_from_index(size_t index) -> V {
    return boost::mp11::mp_with_index<
        boost::mp11::mp_size<V>>(index, [](auto I) {
        return V(
            std::in_place_index<I>,
            SerdeDefaultProvider<std::variant_alternative_t<I, V>>::get());
    });
}

template <IsVariant V>
struct resolve_variant_index {};

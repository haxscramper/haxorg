#pragma once

#include <variant>
#include <hstd/system/string_convert.hpp>
#include <hstd/system/basic_templates.hpp>
#include <hstd/system/Formatter.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/system/macros.hpp>

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

template <IsSubVariantType V>
struct std::formatter<V> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const V& p, FormatContext& ctx) const {
        int field_count = 0;
        for_each_field_with_bases<V>([&]() { ++field_count; });
        fmt_ctx(p.sub_variant_get_kind(), ctx);
        fmt_ctx("(", ctx);
        std::visit(
            [&](auto const& t) { fmt_ctx(t, ctx); },
            p.sub_variant_get_data());
        for_each_field_value_with_bases(
            p, [&](char const* name, auto const& value) {
                if (std::string{name}
                    != std::string{p.sub_variant_get_name()}) {
                    fmt_ctx(", ", ctx);
                    fmt_ctx(".", ctx);
                    fmt_ctx(name, ctx);
                    fmt_ctx(" = ", ctx);
                    fmt_ctx(value);
                }
            });
        return fmt_ctx(")", ctx);
    }
};


template <IsVariant V>
struct std::hash<V> {
    std::size_t operator()(V const& it) const noexcept {
        std::size_t result = 0;
        hax_hash_combine(result, it.index());
        std::visit(
            [&](auto const& var) { hax_hash_combine(result, var); }, it);
        return result;
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

template <IsVariant V>
struct JsonSerde<V> {
    static json to_json(V const& it) {
        auto result     = json::object();
        result["index"] = JsonSerde<int>::to_json(it.index());
        std::visit(
            [&]<typename T>(T const& value) {
                result["value"] = JsonSerde<T>::to_json(value);
            },
            it);

        return result;
    }
    static V from_json(json const& j) {
        V result = variant_from_index<V>(j["index"].get<int>());
        std::visit(
            [&]<typename T>(T& value) {
                value = JsonSerde<T>::from_json(j["value"]);
            },
            result);
    }
};

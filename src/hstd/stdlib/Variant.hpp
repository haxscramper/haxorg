#pragma once

#include <variant>
#include <hstd/system/string_convert.hpp>
#include <hstd/system/basic_templates.hpp>
#include <hstd/system/Formatter.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/system/macros.hpp>
#include <hstd/system/exceptions.hpp>

namespace hstd {

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

struct bad_variant_access : CRTP_hexception<bad_variant_access> {
    template <typename E>
    static bad_variant_access init(
        E           expected,
        E           given,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION(),
        char const* file     = __builtin_FILE()) {
        return CRTP_hexception<bad_variant_access>::init(
            fmt("Variant access mismatch, expected {}::{}, but got {}::{}",
                value_metadata<E>::typeName(),
                expected,
                value_metadata<E>::typeName(),
                given),
            line,
            function,
            file);
    }
};

template <typename T>
concept IsSubVariantType = requires(T t) {
    typename T::variant_enum_type;
    typename T::variant_data_type;
    { t.sub_variant_get_name() } -> std::same_as<char const*>;
};


template <typename T, typename Variant>
constexpr std::size_t variant_index = std::variant_size_v<Variant>;

template <typename T, typename... Types>
constexpr std::size_t variant_index<T, std::variant<T, Types...>> = 0;

template <typename T, typename U, typename... Types>
constexpr std::size_t variant_index<T, std::variant<U, Types...>>
    = 1 + variant_index<T, std::variant<Types...>>;

template <typename T, IsSubVariantType V>
auto& get_sub_variant(auto& variant) {
    if (std::holds_alternative<T>(variant)) {
        return std::get<T>(variant);
    } else {
        throw hstd::bad_variant_access::init(
            static_cast<V::variant_enum_type>(
                variant_index<T, typename V::variant_data_type>),
            static_cast<V::variant_enum_type>(variant.index()));
    }
}


template <typename T>
concept DescribedSubVariantType = IsSubVariantType<T>
                               && DescribedRecord<T>;


template <IsVariant V>
auto variant_from_index(size_t index) -> V {
    return ::boost::mp11::mp_with_index<
        ::boost::mp11::mp_size<V>>(index, [](auto I) {
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


} // namespace hstd


template <hstd::IsVariant V>
struct std::hash<V> {
    std::size_t operator()(V const& it) const noexcept {
        std::size_t result = 0;
        hax_hash_combine(result, it.index());
        std::visit(
            [&](auto const& var) { hax_hash_combine(result, var); }, it);
        return result;
    }
};

template <hstd::DescribedSubVariantType V>
struct std::formatter<V> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const V& p, FormatContext& ctx) const {
        ::hstd::fmt_ctx(p.sub_variant_get_kind(), ctx);
        ::hstd::fmt_ctx("(", ctx);
        std::visit(
            [&](auto const& t) { ::hstd::fmt_ctx(t, ctx); },
            p.sub_variant_get_data());
        ::hstd::for_each_field_value_with_bases(
            p, [&](char const* name, auto const& value) {
                if (std::string{name}
                    != std::string{p.sub_variant_get_name()}) {
                    ::hstd::fmt_ctx(", ", ctx);
                    ::hstd::fmt_ctx(".", ctx);
                    ::hstd::fmt_ctx(name, ctx);
                    ::hstd::fmt_ctx(" = ", ctx);
                    ::hstd::fmt_ctx(value, ctx);
                }
            });
        return ::hstd::fmt_ctx(")", ctx);
    }
};


template <hstd::IsVariant V>
struct std::formatter<V> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(const V& p, FormatContext& ctx) const {
        std::string res;
        ::hstd::fmt_ctx("Var(", ctx);
        ::hstd::fmt_ctx(p.index(), ctx);
        ::hstd::fmt_ctx(": ", ctx);
        std::visit(
            [&ctx](const auto& value) { ::hstd::fmt_ctx(value, ctx); }, p);
        return ::hstd::fmt_ctx(")", ctx);
    }
};

template <typename... Args>
struct hstd::value_metadata<hstd::Variant<Args...>> {
    static std::string typeName() {
        return std::string{"Variant<"}
             + join(", ", Vec<Str>{hstd::value_metadata<Args>::get()...})
             + std::string{">"};
    }
};

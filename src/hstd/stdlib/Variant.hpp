#pragma once

#include <sstream>
#include <variant>
#include <hstd/system/string_convert.hpp>
#include <hstd/system/basic_templates.hpp>

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

// Does not conform to regular `ostream<<` implementation in order to avoid
// implicit conversion from value types. Not sure this can be circumvented
// by disallowing to-argument conversion in some way.
template <IsVariant V>
QTextStream& to_string(QTextStream& os, V const& value) {
    os << "Var(" << value.index() << ": ";
    std::visit(
        [&os](const auto& value) {
            os << value;
            return 0;
        },
        value);
    os << ")";
    return os;
}

template <IsVariant V>
auto variant_from_index(size_t index) -> V {
    return boost::mp11::mp_with_index<
        boost::mp11::mp_size<V>>(index, [](auto I) {
        return V(
            std::in_place_index<I>,
            SerdeDefaultProvider<std::variant_alternative_t<I, V>>::get());
    });
}

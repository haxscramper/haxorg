#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <optional>

#include <boost/mp11.hpp>
#include <boost/describe.hpp>
#include <hstd/system/string_convert.hpp>
#include <hstd/system/basic_typedefs.hpp>

template <typename T>
concept DescribedEnum = IsEnum<T>
                     && boost::describe::has_describe_enumerators<
                            T>::value;

template <DescribedEnum T>
std::string enum_to_string(T value) {
    return boost::describe::enum_to_string(value, "<unnamed>");
}

namespace boost::describe {

inline void throw_invalid_name(char const* name, char const* type) {
    throw std::runtime_error(
        std::string("Invalid enumerator name '") + name
        + "' for enum type '" + type + "'");
}

template <class E>
E string_to_enum(char const* name) {
    bool found = false;
    E    r     = {};

    boost::mp11::mp_for_each<boost::describe::describe_enumerators<E>>(
        [&](auto D) {
            if (!found && std::strcmp(D.name, name) == 0) {
                found = true;
                r     = D.value;
            }
        });

    if (found) {
        return r;
    } else {
        throw_invalid_name(name, typeid(E).name());
    }
}
}; // namespace boost::describe

template <typename T>
std::optional<T> string_to_enum(std::string const&);

template <DescribedEnum T>
std::optional<T> string_to_enum(std::string const& value) {
    try {
        return boost::describe::string_to_enum<T>(value.c_str());
    } catch (...) { return std::nullopt; }
}

template <DescribedEnum T>
std::ostream& operator<<(std::ostream& os, T value) {
    return os << enum_to_string(value);
}

template <class E, template <class... T> class L, class... T>
constexpr std::array<E, sizeof...(T)> describe_enumerators_list(L<T...>) {
    return {{T::value...}};
}

template <class E>
constexpr auto describe_enumerators_as_array() {
    return describe_enumerators_list<E>(
        boost::describe::describe_enumerators<E>());
}

template <DescribedEnum E>
E low() {
    constexpr auto D = describe_enumerators_as_array<E>();
    return D[0];
}


template <DescribedEnum E>
E high() {
    constexpr auto D = describe_enumerators_as_array<E>();
    return D[sizeof(D) / sizeof(E) - 1];
}

#pragma once

#include <iostream>
#include <string>
#include <sstream>

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

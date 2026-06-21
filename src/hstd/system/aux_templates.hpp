#pragma once

#include <hstd/system/basic_typedefs.hpp>
#include <experimental/type_traits>

namespace hstd {

template <int N, int M>
struct pow_v {
    enum
    {
        res = N * pow_v<N, M - 1>::res
    };
};


template <int N>
struct pow_v<N, 0> {
    enum
    {
        res = 1
    };
};


/// Helper type trait to check whether type \tparam Derived is derived from
/// the \tparam Base class - including cases when Base is an
/// partially specialized type name.
template <template <typename...> class Base, typename Derived>
struct is_base_of_template {
    template <typename... Ts>
    static std::true_type test(Base<Ts...> const volatile*);

    static std::false_type test(...);

    static constexpr bool value = decltype(test(
        std::declval<Derived const volatile*>()))::value;
};

template <template <typename...> class Base, typename Derived>
using is_base_of_template_t = typename is_base_of_template<Base, Derived>::type;

/// Convenience helper trait for getting `value` of the trait check
template <template <typename...> class Base, typename Derived>
inline constexpr bool is_base_of_template_v = is_base_of_template<Base, Derived>::value;

/// Type trait to check whether provided T type is in the
/// Pack
template <typename T, typename... Pack>
struct is_in_pack;

template <typename V, typename T0, typename... T>
struct is_in_pack<V, T0, T...> {
    static const bool value = is_in_pack<V, T...>::value;
};

template <typename V, typename... T>
struct is_in_pack<V, V, T...> {
    static const bool value = true;
};

template <typename V>
struct is_in_pack<V> {
    static const bool value = false;
};


/// `::value` accessor for the 'is in pack' type trait
template <typename T, typename... Pack>
inline constexpr bool is_in_pack_v = is_in_pack<T, Pack...>::value;

} // namespace hstd

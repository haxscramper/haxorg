export module hstd.system.aux_templates;

import hstd.system.basic_typedefs;
import std;

export {
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
    // A function which can only be called by something convertible to a
    // Base<Ts...>*
    template <typename... Ts>
    static auto constexpr is_callable(Base<Ts...>*) -> arg_pack<Ts...>;

    // Detector, will return type of calling is_callable, or it won't
    // compile if that can't be done
    template <typename T>
    using is_callable_t = decltype(is_callable(std::declval<T*>()));

    // Is it possible to call is_callable which the Derived type
    static inline constexpr bool value = std::experimental::
        is_detected_v<is_callable_t, Derived>;

    // If it is possible to call is_callable with the Derived type what
    // would it return, if not type is a void
    using type = std::experimental::
        detected_or_t<void, is_callable_t, Derived>;
};

template <template <typename...> class Base, typename Derived>
using is_base_of_template_t = typename is_base_of_template<Base, Derived>::
    type;

/// Convenience helper trait for getting `value` of the trait check
template <template <typename...> class Base, typename Derived>
inline constexpr bool is_base_of_template_v = is_base_of_template<
    Base,
    Derived>::value;

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
}
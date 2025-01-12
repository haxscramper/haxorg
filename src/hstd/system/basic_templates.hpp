#pragma once

#include <concepts>
#include <limits>
#include <algorithm>

#include <hstd/system/basic_typedefs.hpp>


#ifdef __GNUG__
#    include <cstdlib>
#    include <memory>
#    include <cxxabi.h>

template <typename T>
constexpr std::string_view get_type_name_fallback() {
#    if defined(__clang__)
    std::string_view p = __PRETTY_FUNCTION__;
    return std::string_view(p.data() + 34, p.size() - 35);
#    elif defined(__GNUG__)
    std::string_view p = __PRETTY_FUNCTION__;
    return std::string_view(p.data() + 49, p.find(';', 49) - 49);
#    else
    return "unknown";
#    endif
}


inline std::string demangle(const char* name) {

    int status = -4; // some arbitrary value to eliminate the compiler
                     // warning

    // enable c++11 by passing the flag -std=c++11 to g++
    std::unique_ptr<char, void (*)(void*)> res{
        abi::__cxa_demangle(name, NULL, NULL, &status), std::free};

    return (status == 0) ? res.get() : name;
}

#else

// does nothing if not g++
inline std::string demangle(const char* name) { return name; }

#endif

/// \brief get next value
template <typename T>
struct value_domain;

template <typename T>
concept ImplementsSucc = requires(CR<T> value) {
    { value_domain<T>::succ(value) } -> std::same_as<T>;
};

template <typename T>
concept ImplementsPrev = requires(CR<T> value) {
    { value_domain<T>::prev(value) } -> std::same_as<T>;
};


template <typename T>
concept ImplementsLow = requires(CR<T> value) {
    { value_domain<T>::low() } -> std::same_as<T>;
};

template <typename T>
concept ImplementsHigh = requires(CR<T> value) {
    { value_domain<T>::high() } -> std::same_as<T>;
};

template <typename T>
concept ImplementsOrd = requires(CR<T> value) {
    { value_domain<T>::ord(value) } -> std::convertible_to<long long int>;
};

template <std::integral T>
struct value_domain<T> {
    static inline T low() { return std::numeric_limits<T>::min(); }
    static inline T high() { return std::numeric_limits<T>::max(); }
    static inline T succ(T const& val) { return val + 1; }
    static inline T prev(T const& val) { return val - 1; }
    static inline long long int ord(T const& val) {
        return static_cast<int>(val);
    }
};

template <typename T>
struct value_metadata {
    static bool        isEmpty(T const& value) { return false; }
    static bool        isNil(T const& value) { return false; }
    static std::string typeName() {
#if defined(__GXX_RTTI) || defined(_CPPRTTI)
        return ::demangle(typeid(T).name());
#else
        return std::string{::get_type_name_fallback<T>()};
#endif
    }
};


template <typename E, E Low, E High>
struct value_domain_ungapped {
    static inline E low() { return Low; }
    static inline E high() { return High; }


    static inline E succ(E value) {
        if constexpr (std::is_enum_v<E>) {
            return static_cast<E>(
                static_cast<std::underlying_type_t<E>>(value) + 1);
        } else {
            return value + 1;
        }
    }

    static inline E prev(E value) {
        if constexpr (std::is_enum_v<E>) {
            return static_cast<E>(
                static_cast<std::underlying_type_t<E>>(value) - 1);
        } else {
            return value - 1;
        }
    }

    static inline long long int ord(E value) {
        return static_cast<long long int>(value)
             - static_cast<long long int>(Low);
    }
};


template <std::integral T, std::integral Other>
T saturating_add(T value, Other change) {
    T res = value + change;
    // Can only happen due to overflow
    if (res < value) { res = value_domain<T>::high(); }
    return res;
}

template <std::integral T, std::integral Other>
T saturating_sub(T value, Other change) {
    T res = value - change;
    // Can only happen due to overflow
    if (value < res) { res = value_domain<T>::low(); }
    return res;
}

template <std::integral T, std::integral Other>
T saturating_add_any(T value, Other change) {
    if (0 <= change) {
        return saturating_add(value, change);
    } else {
        return saturating_sub(value, std::abs(change));
    }
}


template <typename T>
concept DefaultConstructible = std::is_default_constructible_v<T>;

template <typename T>
struct SerdeDefaultProvider {};

template <DefaultConstructible T>
struct SerdeDefaultProvider<T> {
    static T get() { return T{}; }
};

template <>
struct value_domain<char> {
    static inline char          low() { return '\x00'; }
    static inline char          high() { return '\xFF'; }
    static inline long long int ord(char c) {
        int res = static_cast<int>(c);
        if (res < 0) {
            return res + 256;
        } else {
            return res;
        }
    }

    static inline char succ(char c) { return char(c + 1); }
};

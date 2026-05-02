#pragma once

#include <variant>
#include <hstd/system/basic_templates.hpp>
#include <hstd/system/macros.hpp>
#include <hstd/system/exceptions.hpp>
#include <hstd/stdlib/strutils.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/system/macros.hpp>


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
        std::string msg = "Variant access mismatch, expected ";
        msg += value_metadata<E>::typeName();
        if constexpr (hstd::IsEnum<E>) {
            msg += "::" + hstd::enum_to_string(expected);
        } else {
            msg += "::" + std::to_string(expected);
        }
        msg += " but got ";
        msg += value_metadata<E>::typeName();
        if constexpr (hstd::IsEnum<E>) {
            msg += "::" + hstd::enum_to_string(given);
        } else {
            msg += "::" + std::to_string(given);
        }
        return CRTP_hexception<bad_variant_access>::init(
            msg, line, function, file);
    }
};

template <size_t _Np, typename... _Types>
constexpr std::variant_alternative_t<_Np, std::variant<_Types...>> const& variant_get(
    std::variant<_Types...> const& __v) {
    static_assert(
        _Np < sizeof...(_Types),
        "The index must be in [0, number of alternatives)");
    if (__v.index() != _Np) {
        throw bad_variant_access::init(_Np, __v.index());
    } else {
        return std::get<_Np>(__v);
    }
}

template <size_t _Np, typename... _Types>
constexpr std::variant_alternative_t<_Np, std::variant<_Types...>>& variant_get(
    std::variant<_Types...>& __v) {
    static_assert(
        _Np < sizeof...(_Types),
        "The index must be in [0, number of alternatives)");
    if (__v.index() != _Np) {
        throw bad_variant_access::init(_Np, __v.index());
    } else {
        return std::get<_Np>(__v);
    }
}

template <typename T>
concept IsSubVariantType = requires(T t) {
    typename T::variant_enum_type;
    typename T::variant_data_type;
    { T::sub_variant_get_name() } -> std::same_as<char const*>;
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

template <typename... Args>
struct hstd::value_metadata<hstd::Variant<Args...>> {
    static bool isEmpty(hstd::Variant<Args...> const& value) {
        return std::visit(
            []<typename Arg>(Arg const& arg) {
                return hstd::value_metadata<Arg>::isEmpty(arg);
            },
            value);
    }

    static std::string typeName() {
        return Str{"Variant<"}
             + Str{", "}.join(
                 Vec<Str>{hstd::value_metadata<Args>::typeName()...})
             + Str{">"};
    }
};

/// \internal Generate getter methods for SUB_VARIANTS

#define __SUB_VARIANT_GETTER(fieldName, Type)                             \
    Type& get##Type() {                                                   \
        return ::hstd::                                                   \
            get_sub_variant<Type, std::remove_cvref_t<decltype(*this)>>(  \
                fieldName);                                               \
    }                                                                     \
                                                                          \
    Type const& get##Type() const {                                       \
        return ::hstd::                                                   \
            get_sub_variant<Type, std::remove_cvref_t<decltype(*this)>>(  \
                fieldName);                                               \
    }                                                                     \
                                                                          \
    bool is##Type() const {                                               \
        return std::holds_alternative<Type>(fieldName);                   \
    }


#define __SUB_VARIANT_GETTER_REFL(fieldName, Type)                        \
    [[refl]] Type& get##Type() {                                          \
        return ::hstd::                                                   \
            get_sub_variant<Type, std::remove_cvref_t<decltype(*this)>>(  \
                fieldName);                                               \
    }                                                                     \
                                                                          \
    [[refl]] Type const& get##Type() const {                              \
        return ::hstd::                                                   \
            get_sub_variant<Type, std::remove_cvref_t<decltype(*this)>>(  \
                fieldName);                                               \
    }                                                                     \
                                                                          \
    [[refl]] bool is##Type() const {                                      \
        return std::holds_alternative<Type>(fieldName);                   \
    }

/// \internal Generate kind getter lambda for SUB_VARIANTS
#define __SUB_VARIANT_KIND_LAMBDA(EnumName, Type)                         \
    [](Type const&) -> EnumName { return EnumName::Type; },

#define __SUB_VARIANTS_REFL_CONCEPT_SERVICE(                              \
    EnumName, VariantName, fieldName, kindGetterName)                     \
    using variant_enum_type = EnumName;                                   \
    using variant_data_type = VariantName;                                \
    EnumName sub_variant_get_kind() const { return kindGetterName(); }    \
    VariantName const& sub_variant_get_data() const { return fieldName; } \
    static char const* sub_variant_get_name() { return #fieldName; }      \
    static char const* sub_variant_get_enum_name() { return #EnumName; }

/**

\brief Helper macro for better API when working with discriminant objects.

\arg EnumName name of the enumeration that is defined to list possible
     variant values
\arg VariantName Name of the variant type for wrapping
     all results
\arg fieldName Name of the field that is used to store
     variant value for a type
\arg kindGetterName name of the method for getting kind from the field.
     Also defines static function that can be used to access the kind
     of the raw variant value.

\snippet sem/SemOrg.hpp declare variant field for subtree properties

This will generate `getKind()` and `static getKind(Data const&)`
methods, define `Data` as `std::variant<Ordered, ...>` and implement
`getOrdered()`, `getTrigger()` etc. for all provided types

\code{.cpp}
struct EditTarget {
    struct Existing { // define first type for variant
        DiaUniqId target;
    };
    struct LastCreated { // second type for variant
    };
    // this Sub-variant will declare
    // - `using Data = std::variant<....`
    // - enum `Kind` with the values `Existing` and `LastCreated`
    // - series of methods `is<Kind>`, and `get<Kind>` for accessing
    //   the specific variant of the object
    // - `getKind()` method that will return the kind based on teh
    //   variant index.
    SUB_VARIANTS(Kind, Data, data, getKind, Existing, LastCreated);
    // `Data` field must be declared separately.
    Data data;
};
\endcode

When using `EditTarget` from the example above, it is possible either
`std::visit()` on the data, `switch (getKind())`  or check for the
individual values with `isExisting()` + `getExisting()`.

**/
#define SUB_VARIANTS_REFL(                                                \
    EnumName, VariantName, fieldName, kindGetterName, ...)                \
    enum class [[refl]] EnumName : unsigned short int                     \
    {                                                                     \
        __VA_ARGS__                                                       \
    };                                                                    \
    BOOST_DESCRIBE_NESTED_ENUM(EnumName, __VA_ARGS__);                    \
    using VariantName = std::variant<__VA_ARGS__>;                        \
    FOR_EACH_CALL_WITH_PASS(                                              \
        __SUB_VARIANT_GETTER_REFL, (fieldName), __VA_ARGS__)              \
    static EnumName kindGetterName(VariantName const& __input) {          \
        return std::visit(                                                \
            ::hstd::overloaded{FOR_EACH_CALL_WITH_PASS(                   \
                __SUB_VARIANT_KIND_LAMBDA, (EnumName), __VA_ARGS__)},     \
            __input);                                                     \
    }                                                                     \
    [[refl]] EnumName kindGetterName() const {                            \
        return kindGetterName(fieldName);                                 \
    }                                                                     \
    __SUB_VARIANTS_REFL_CONCEPT_SERVICE(                                  \
        EnumName, VariantName, fieldName, kindGetterName)


#define SUB_VARIANTS(                                                     \
    EnumName, VariantName, fieldName, kindGetterName, ...)                \
    enum class EnumName : unsigned short int                              \
    {                                                                     \
        __VA_ARGS__                                                       \
    };                                                                    \
    BOOST_DESCRIBE_NESTED_ENUM(EnumName, __VA_ARGS__);                    \
    using VariantName = std::variant<__VA_ARGS__>;                        \
    FOR_EACH_CALL_WITH_PASS(                                              \
        __SUB_VARIANT_GETTER, (fieldName), __VA_ARGS__)                   \
    static EnumName kindGetterName(VariantName const& __input) {          \
        return std::visit(                                                \
            ::hstd::overloaded{FOR_EACH_CALL_WITH_PASS(                   \
                __SUB_VARIANT_KIND_LAMBDA, (EnumName), __VA_ARGS__)},     \
            __input);                                                     \
    }                                                                     \
    EnumName kindGetterName() const { return kindGetterName(fieldName); } \
    __SUB_VARIANTS_REFL_CONCEPT_SERVICE(                                  \
        EnumName, VariantName, fieldName, kindGetterName)

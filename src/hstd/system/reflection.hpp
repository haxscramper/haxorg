#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <optional>

#include <boost/mp11.hpp>
#include <boost/describe.hpp>
#include <hstd/system/string_convert.hpp>
#include <hstd/system/basic_typedefs.hpp>
#include <hstd/system/basic_templates.hpp>
#include <vector>
#include <format>
#include <type_traits>


template <typename T>
inline void hax_hash_combine(std::size_t& seed, const T& v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}


template <typename T>
struct value_metadata<std::vector<T>> {
    static bool isEmpty(std::vector<T> const& value) {
        return value.empty();
    }
};

template <typename T>
struct value_metadata<std::optional<T>> {
    static bool isEmpty(std::optional<T> const& value) {
        return !value.has_value() || value_metadata<T>::isEmpty(*value);
    }

    static bool isNil(std::optional<T> const& value) {
        return !value.has_value();
    }
};

template <typename T>
struct value_metadata<T*> {
    static bool isEmpty(T* const& value) { return value == nullptr; }
    static bool isNil(T* const& value) { return value == nullptr; }
};

template <typename T>
struct value_metadata<T const*> {
    static bool isEmpty(T const* const& value) { return value == nullptr; }
    static bool isNil(T const* const& value) { return value == nullptr; }
};


template <>
struct value_metadata<std::string> {
    static bool isEmpty(std::string const& value) { return value.empty(); }
};


template <typename T>
concept IsEnum = std::is_enum<T>::value;

template <typename T>
concept IsRecord = std::is_class<T>::value;

template <typename T>
concept DescribedEnum = IsEnum<T>
                     && boost::describe::has_describe_enumerators<
                            T>::value;

template <typename T>
concept DescribedRecord = boost::describe::has_describe_members<
                              std::remove_cvref_t<T>>::value
                       && boost::describe::has_describe_bases<
                              std::remove_cvref_t<T>>::value;

namespace boost::describe {

[[noreturn]] inline void throw_invalid_name(
    char const* name,
    char const* type) {
    throw std::runtime_error(
        (std::string("Invalid enumerator name '") + name
         + "' for enum type '" + type + "'"));
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
        throw_invalid_name(
            name,
#ifdef __cpp_rtti
            typeid(E).name()
#else
            ""
#endif
        );
    }
}
}; // namespace boost::describe

template <typename E>
struct enum_serde;

template <typename T>
concept SerializableEnum = IsEnum<T> && requires(CR<T> value) {
    { enum_serde<T>::to_string(value) } -> std::same_as<std::string>;
};

template <typename T>
concept NonSerializableEnum = IsEnum<T> && !SerializableEnum<T>;


template <SerializableEnum T>
struct std::formatter<T> : std::formatter<std::string> {
    using FmtType = T;
    template <typename FormatContext>
    FormatContext::iterator format(FmtType const& p, FormatContext& ctx)
        const {
        std::formatter<std::string> fmt;
        return fmt.format(enum_serde<T>::to_string(p), ctx);
    }
};


template <NonSerializableEnum T>
struct std::formatter<T> : std::formatter<std::string> {
    using FmtType = T;
    template <typename FormatContext>
    FormatContext::iterator format(FmtType const& p, FormatContext& ctx)
        const {
        std::formatter<std::string> fmt;
        return fmt.format(std::to_string((int)p), ctx);
    }
};


template <DescribedEnum E>
struct enum_serde<E> {
    static inline std::string to_string(E const& value) {
        return boost::describe::enum_to_string(value, "<unnamed>");
    }

    static inline std::optional<E> from_string(std::string const& str) {
        try {
            std::string tmp = str;
            return boost::describe::string_to_enum<E>(tmp.c_str());
        } catch (...) { return std::nullopt; }
    }
};

template <class E, template <class... T> class L, class... T>
constexpr std::array<E, sizeof...(T)> describe_enumerators_list(L<T...>) {
    return {{T::value...}};
}

template <class E>
constexpr auto describe_enumerators_as_array() {
    return describe_enumerators_list<E>(
        boost::describe::describe_enumerators<E>());
}

template <class E>
struct EnumFieldDesc {
    std::string name;
    E           value;
    int         index;
};

template <class E>
std::vector<EnumFieldDesc<E>> describe_enumerators() {
    constexpr auto D = describe_enumerators_as_array<E>();

    std::vector<EnumFieldDesc<E>> result;
    for (int i = 0; i < D.size(); ++i) {
        result.push_back(EnumFieldDesc<E>{
            .index = i,
            .value = D[i],
            .name  = enum_serde<E>::to_string(D[i]),
        });
    }

    return result;
}

template <class E>
std::vector<std::string> enumerator_names() {
    auto                     tmp = ::describe_enumerators<E>();
    std::vector<std::string> result;
    for (const auto& it : tmp) { result.push_back(it.name); }
    return result;
}


template <DescribedEnum E>
struct value_domain<E> {
    static constexpr auto D = describe_enumerators_as_array<E>();

    static inline E low() { return D[0]; }
    static inline E high() { return D[sizeof(D) / sizeof(E) - 1]; }
    static inline E succ(E const& value) { return D[ord(value) + 1]; }
    static inline E prev(E const& value) { return D[ord(value) - 1]; }

    static inline long long int ord(E const& value) {
        for (int i = 0; i < sizeof(D) / sizeof(E); i++) {
            if (D[i] == value) { return i; }
        }
        return -1;
    }
};


template <
    class T,
    class Bd = boost::describe::
        describe_bases<T, boost::describe::mod_any_access>,
    class Md = boost::describe::
        describe_members<T, boost::describe::mod_any_access>,
    class En = std::enable_if_t<!std::is_union<T>::value>>
std::string described_class_printer(T const& t) {
    std::string result;
    result += "{";

    bool first = true;

    boost::mp11::mp_for_each<Bd>([&](auto D) {
        if (!first) { result += ", "; }
        first = false;

        using B = typename decltype(D)::type;
        result += described_class_printer((B const&)t);
    });

    boost::mp11::mp_for_each<Md>([&](auto D) {
        if (!first) { result += ", "; }
        first = false;

        result += std::format(".{} = {}", D.name, t.*D.pointer);
    });

    result += "}";
    return result;
}

template <DescribedRecord R>
struct std::formatter<R> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(R const& p, FormatContext& ctx) const {
        std::formatter<std::string> fmt;
        return fmt.format(described_class_printer(p), ctx);
    }
};


template <typename T, typename Func>
void for_each_field_with_bases(Func cb, bool pre_bases = true) {
    if (pre_bases) {
        boost::mp11::mp_for_each<boost::describe::describe_bases<
            T,
            boost::describe::mod_any_access>>([&](auto Base) {
            for_each_field_with_bases<typename decltype(Base)::type>(
                cb, pre_bases);
        });
    }

    boost::mp11::mp_for_each<boost::describe::describe_members<
        T,
        boost::describe::mod_any_access>>(cb);

    if (!pre_bases) {
        boost::mp11::mp_for_each<boost::describe::describe_bases<
            T,
            boost::describe::mod_any_access>>([&](auto Base) {
            for_each_field_with_bases<typename decltype(Base)::type>(
                cb, pre_bases);
        });
    }
}

template <typename T>
bool equal_on_all_fields(CR<T> lhs, CR<T> rhs) {
    bool equal = true;

    for_each_field_with_bases<T>([&](auto const& field) {
        equal &= (lhs.*field.pointer == rhs.*field.pointer);
    });

    return equal;
}


#define REFL_DEFINE_DESCRIBED_FORMATTER(__TypeName)                       \
    template <>                                                           \
    struct std::formatter<__TypeName> : std::formatter<std::string> {     \
        template <typename FormatContext>                                 \
        FormatContext::iterator format(                                   \
            const __TypeName& value,                                      \
            FormatContext&    ctx) const {                                   \
            std::formatter<std::string> fmt;                              \
            return fmt.format(described_class_printer(value), ctx);       \
        }                                                                 \
    };


template <typename T>
struct __DescFieldTypeHelper {};

/// \brief Get type of the boost::describe field descriptor.
#define DESC_FIELD_TYPE(__field)                                          \
    __DescFieldTypeHelper<decltype(__field.pointer)>::Type

template <typename StructType, typename FieldType>
struct __DescFieldTypeHelper<FieldType StructType::*> {
    using Type = std::remove_cvref_t<FieldType>;
};

template <typename StructType, typename FieldType>
struct __DescFieldTypeHelper<FieldType StructType::*const> {
    using Type = std::remove_cvref_t<FieldType>;
};


// clang-format off

// They thought 52 arguments would be enough for anyone ...

#define BOOST_DESCRIBE_PP_FOR_EACH_0(F, a)
#define BOOST_DESCRIBE_PP_FOR_EACH_1(F, a, x) BOOST_DESCRIBE_PP_CALL(F, a, x)
#define BOOST_DESCRIBE_PP_FOR_EACH_2(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_1(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_3(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_2(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_4(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_3(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_5(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_4(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_6(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_5(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_7(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_6(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_8(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_7(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_9(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_8(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_10(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_9(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_11(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_10(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_12(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_11(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_13(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_12(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_14(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_13(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_15(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_14(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_16(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_15(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_17(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_16(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_18(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_17(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_19(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_18(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_20(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_19(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_21(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_20(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_22(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_21(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_23(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_22(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_24(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_23(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_25(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_24(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_26(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_25(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_27(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_26(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_28(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_27(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_29(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_28(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_30(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_29(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_31(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_30(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_32(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_31(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_33(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_32(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_34(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_33(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_35(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_34(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_36(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_35(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_37(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_36(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_38(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_37(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_39(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_38(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_40(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_39(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_41(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_40(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_42(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_41(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_43(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_42(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_44(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_43(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_45(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_44(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_46(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_45(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_47(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_46(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_48(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_47(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_49(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_48(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_50(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_49(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_51(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_50(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_52(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_51(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_53(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_52(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_54(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_53(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_55(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_54(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_56(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_55(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_57(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_56(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_58(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_57(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_59(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_58(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_60(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_59(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_61(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_60(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_62(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_61(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_63(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_62(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_64(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_63(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_65(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_64(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_66(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_65(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_67(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_66(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_68(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_67(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_69(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_68(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_70(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_69(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_71(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_70(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_72(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_71(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_73(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_72(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_74(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_73(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_75(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_74(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_76(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_75(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_77(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_76(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_78(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_77(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_79(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_78(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_80(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_79(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_81(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_80(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_82(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_81(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_83(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_82(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_84(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_83(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_85(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_84(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_86(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_85(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_87(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_86(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_88(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_87(F, a, __VA_ARGS__))
#define BOOST_DESCRIBE_PP_FOR_EACH_89(F, a, x, ...) BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_CALL(F, a, x) BOOST_DESCRIBE_PP_FOR_EACH_88(F, a, __VA_ARGS__))

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmacro-redefined"

#define BOOST_DESCRIBE_PP_FE_EXTRACT(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _77, _76, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, V, ...) V

#define BOOST_DESCRIBE_PP_FOR_EACH(F, ...) \
    BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_FE_EXTRACT(__VA_ARGS__, \
    BOOST_DESCRIBE_PP_FOR_EACH_89, \
    BOOST_DESCRIBE_PP_FOR_EACH_88, \
    BOOST_DESCRIBE_PP_FOR_EACH_87, \
    BOOST_DESCRIBE_PP_FOR_EACH_86, \
    BOOST_DESCRIBE_PP_FOR_EACH_85, \
    BOOST_DESCRIBE_PP_FOR_EACH_84, \
    BOOST_DESCRIBE_PP_FOR_EACH_83, \
    BOOST_DESCRIBE_PP_FOR_EACH_82, \
    BOOST_DESCRIBE_PP_FOR_EACH_81, \
    BOOST_DESCRIBE_PP_FOR_EACH_80, \
    BOOST_DESCRIBE_PP_FOR_EACH_79, \
    BOOST_DESCRIBE_PP_FOR_EACH_78, \
    BOOST_DESCRIBE_PP_FOR_EACH_77, \
    BOOST_DESCRIBE_PP_FOR_EACH_76, \
    BOOST_DESCRIBE_PP_FOR_EACH_75, \
    BOOST_DESCRIBE_PP_FOR_EACH_74, \
    BOOST_DESCRIBE_PP_FOR_EACH_73, \
    BOOST_DESCRIBE_PP_FOR_EACH_72, \
    BOOST_DESCRIBE_PP_FOR_EACH_71, \
    BOOST_DESCRIBE_PP_FOR_EACH_70, \
    BOOST_DESCRIBE_PP_FOR_EACH_69, \
    BOOST_DESCRIBE_PP_FOR_EACH_68, \
    BOOST_DESCRIBE_PP_FOR_EACH_67, \
    BOOST_DESCRIBE_PP_FOR_EACH_66, \
    BOOST_DESCRIBE_PP_FOR_EACH_65, \
    BOOST_DESCRIBE_PP_FOR_EACH_64, \
    BOOST_DESCRIBE_PP_FOR_EACH_63, \
    BOOST_DESCRIBE_PP_FOR_EACH_62, \
    BOOST_DESCRIBE_PP_FOR_EACH_61, \
    BOOST_DESCRIBE_PP_FOR_EACH_60, \
    BOOST_DESCRIBE_PP_FOR_EACH_59, \
    BOOST_DESCRIBE_PP_FOR_EACH_58, \
    BOOST_DESCRIBE_PP_FOR_EACH_57, \
    BOOST_DESCRIBE_PP_FOR_EACH_56, \
    BOOST_DESCRIBE_PP_FOR_EACH_55, \
    BOOST_DESCRIBE_PP_FOR_EACH_54, \
    BOOST_DESCRIBE_PP_FOR_EACH_53, \
    BOOST_DESCRIBE_PP_FOR_EACH_52, \
    BOOST_DESCRIBE_PP_FOR_EACH_51, \
    BOOST_DESCRIBE_PP_FOR_EACH_50, \
    BOOST_DESCRIBE_PP_FOR_EACH_49, \
    BOOST_DESCRIBE_PP_FOR_EACH_48, \
    BOOST_DESCRIBE_PP_FOR_EACH_47, \
    BOOST_DESCRIBE_PP_FOR_EACH_46, \
    BOOST_DESCRIBE_PP_FOR_EACH_45, \
    BOOST_DESCRIBE_PP_FOR_EACH_44, \
    BOOST_DESCRIBE_PP_FOR_EACH_43, \
    BOOST_DESCRIBE_PP_FOR_EACH_42, \
    BOOST_DESCRIBE_PP_FOR_EACH_41, \
    BOOST_DESCRIBE_PP_FOR_EACH_40, \
    BOOST_DESCRIBE_PP_FOR_EACH_39, \
    BOOST_DESCRIBE_PP_FOR_EACH_38, \
    BOOST_DESCRIBE_PP_FOR_EACH_37, \
    BOOST_DESCRIBE_PP_FOR_EACH_36, \
    BOOST_DESCRIBE_PP_FOR_EACH_35, \
    BOOST_DESCRIBE_PP_FOR_EACH_34, \
    BOOST_DESCRIBE_PP_FOR_EACH_33, \
    BOOST_DESCRIBE_PP_FOR_EACH_32, \
    BOOST_DESCRIBE_PP_FOR_EACH_31, \
    BOOST_DESCRIBE_PP_FOR_EACH_30, \
    BOOST_DESCRIBE_PP_FOR_EACH_29, \
    BOOST_DESCRIBE_PP_FOR_EACH_28, \
    BOOST_DESCRIBE_PP_FOR_EACH_27, \
    BOOST_DESCRIBE_PP_FOR_EACH_26, \
    BOOST_DESCRIBE_PP_FOR_EACH_25, \
    BOOST_DESCRIBE_PP_FOR_EACH_24, \
    BOOST_DESCRIBE_PP_FOR_EACH_23, \
    BOOST_DESCRIBE_PP_FOR_EACH_22, \
    BOOST_DESCRIBE_PP_FOR_EACH_21, \
    BOOST_DESCRIBE_PP_FOR_EACH_20, \
    BOOST_DESCRIBE_PP_FOR_EACH_19, \
    BOOST_DESCRIBE_PP_FOR_EACH_18, \
    BOOST_DESCRIBE_PP_FOR_EACH_17, \
    BOOST_DESCRIBE_PP_FOR_EACH_16, \
    BOOST_DESCRIBE_PP_FOR_EACH_15, \
    BOOST_DESCRIBE_PP_FOR_EACH_14, \
    BOOST_DESCRIBE_PP_FOR_EACH_13, \
    BOOST_DESCRIBE_PP_FOR_EACH_12, \
    BOOST_DESCRIBE_PP_FOR_EACH_11, \
    BOOST_DESCRIBE_PP_FOR_EACH_10, \
    BOOST_DESCRIBE_PP_FOR_EACH_9, \
    BOOST_DESCRIBE_PP_FOR_EACH_8, \
    BOOST_DESCRIBE_PP_FOR_EACH_7, \
    BOOST_DESCRIBE_PP_FOR_EACH_6, \
    BOOST_DESCRIBE_PP_FOR_EACH_5, \
    BOOST_DESCRIBE_PP_FOR_EACH_4, \
    BOOST_DESCRIBE_PP_FOR_EACH_3, \
    BOOST_DESCRIBE_PP_FOR_EACH_2, \
    BOOST_DESCRIBE_PP_FOR_EACH_1, \
    BOOST_DESCRIBE_PP_FOR_EACH_0))(F, __VA_ARGS__))

#pragma clang diagnostic pop
// clang-format on

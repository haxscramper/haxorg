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
QString enum_to_string(T value) {
    return boost::describe::enum_to_string(value, "<unnamed>");
}

namespace boost::describe {

inline void throw_invalid_name(char const* name, char const* type) {
    throw std::runtime_error((QString("Invalid enumerator name '") + name
                              + "' for enum type '" + type + "'")
                                 .toStdString());
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
std::optional<T> string_to_enum(QString const&);

template <DescribedEnum T>
std::optional<T> string_to_enum(QString const& value) {
    try {
        std::string tmp = value.toStdString();
        return boost::describe::string_to_enum<T>(tmp.c_str());
    } catch (...) { return std::nullopt; }
}

template <DescribedEnum T>
QTextStream& operator<<(QTextStream& os, T value) {
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

template <class E>
struct EnumFieldDesc {
    QString name;
    E       value;
    int     index;
};

template <class E>
std::vector<EnumFieldDesc<E>> describe_enumerators() {
    constexpr auto D = describe_enumerators_as_array<E>();

    std::vector<EnumFieldDesc<E>> result;
    for (int i = 0; i < D.size(); ++i) {
        result.push_back(EnumFieldDesc<E>{
            .index = i,
            .value = D[i],
            .name  = enum_to_string(D[i]),
        });
    }

    return result;
}

template <class E>
std::vector<QString> enumerator_names() {
    auto                 tmp = describe_enumerators<E>();
    std::vector<QString> result;
    for (const auto& it : tmp) {
        result.push_back(it.name);
    }
    return result;
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


template <
    class T,
    class Bd = boost::describe::
        describe_bases<T, boost::describe::mod_any_access>,
    class Md = boost::describe::
        describe_members<T, boost::describe::mod_any_access>,
    class En = std::enable_if_t<!std::is_union<T>::value>>
QTextStream& described_class_printer(QTextStream& os, T const& t) {
    os << "{";

    bool first = true;

    boost::mp11::mp_for_each<Bd>([&](auto D) {
        if (!first) {
            os << ", ";
        }
        first = false;

        using B = typename decltype(D)::type;
        os << (B const&)t;
    });

    boost::mp11::mp_for_each<Md>([&](auto D) {
        if (!first) {
            os << ", ";
        }
        first = false;

        os << "." << D.name << " = " << t.*D.pointer;
    });

    os << "}";
    return os;
}

#define REFL_DEFINE_DESCRIBED_OSTREAM(TypeName)                           \
    inline QTextStream& operator<<(                                       \
        QTextStream& os, CR<TypeName> const& value) {                     \
        return os << described_class_printer(os, value);                  \
    }

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

#define BOOST_DESCRIBE_PP_FE_EXTRACT(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, V, ...) V

#define BOOST_DESCRIBE_PP_FOR_EACH(F, ...) \
    BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_EXPAND(BOOST_DESCRIBE_PP_FE_EXTRACT(__VA_ARGS__, \
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

// clang-format on

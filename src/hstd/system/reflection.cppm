module;

#include <iostream>
#include <string>
#include <sstream>
#include <optional>

#include <boost/mp11.hpp>
#include <boost/describe.hpp>

#include <vector>
#include <format>
#include <type_traits>

export module hstd.system.reflection;

import std.system.string_convert;
import std.system.basic_typedefs;
import std.system.basic_templates;

export {
template <typename T>
concept IsEnum = std::is_enum<T>::value;

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

inline void throw_invalid_name(char const* name, char const* type) {
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
        throw_invalid_name(name, typeid(E).name());
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
    for (const auto& it : tmp) {
        result.push_back(it.name);
    }
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
            if (D[i] == value) {
                return i;
            }
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
        if (!first) {
            result += ", ";
        }
        first = false;

        using B = typename decltype(D)::type;
        result += (B const&)t;
    });

    boost::mp11::mp_for_each<Md>([&](auto D) {
        if (!first) {
            result += ", ";
        }
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
}
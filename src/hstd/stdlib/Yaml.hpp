#pragma once

#pragma warning(push, 0)
#include <yaml-cpp/yaml.h>
#pragma warning(pop)

#include <hstd/stdlib/Str.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <boost/mp11.hpp>
#include <hstd/stdlib/Formatter.hpp>

using yaml = YAML::Node;

namespace hstd {

struct BadTypeConversion : public YAML::RepresentationException {
    explicit BadTypeConversion(YAML::Mark mark, std::string const& message)
        : YAML::RepresentationException(mark, message) {}
};


template <typename E>
inline E to_enum(yaml const& in, E fallback) {
    return string_to_enum<E>(in.as<std::string>()).value_or(fallback);
}

template <typename T>
inline void maybe_field(yaml const& in, T& out, std::string name) {
    if (in[name]) { out = in[name].as<T>(); }
}

template <typename E>
inline void maybe_enum_field(yaml const& in, E& out, std::string name, E fallback) {
    if (in[name]) { out = to_enum<E>(in[name], fallback); }
}

} // namespace hstd


template <>
struct fmt::formatter<YAML::Mark> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(YAML::Mark const& p, fmt::format_context& ctx) const {
        if (p.is_null()) {
            return hstd::fmt_ctx("null", ctx);
        } else {
            hstd::fmt_ctx(p.pos, ctx);
            hstd::fmt_ctx(":", ctx);
            hstd::fmt_ctx(p.line, ctx);
            hstd::fmt_ctx(":", ctx);
            return hstd::fmt_ctx(p.column, ctx);
        }
    }
};

template <>
struct fmt::formatter<yaml> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(yaml const& p, fmt::format_context& ctx) const {
        std::stringstream os;
        os << p;
        return hstd::fmt_ctx(os.str(), ctx);
    }
};


namespace YAML {
template <typename T>
struct convert<std::optional<T>> {
    static Node encode(std::optional<T> const& str) {
        if (str.has_value()) {
            return convert<T>().encode(str.value());
        } else {
            return Node();
        }
    }
    static bool decode(Node const& in, std::optional<T>& out) {
        if (!in.IsNull()) {
            T tmp;
            convert<T>().decode(in, tmp);
            out = tmp;
        } else {
            out = std::nullopt;
        }
        return true;
    }
};

template <hstd::IsEnum E>
struct convert<E> {
    static Node encode(E const& str) {
        Node result;
        result = enum_to_string(str);
        return result;
    }
    static bool decode(Node const& in, E& out) {
        auto res = hstd::enum_serde<E>::from_string(in.as<std::string>());
        if (res.has_value()) {
            out = res.value();
            return true;
        } else {
            throw hstd::BadTypeConversion(
                in.Mark(),
                hstd::fmt(
                    "Could not convert {} to {}", in, hstd::demangle(typeid(E).name())));
        }
    }
};

template <>
struct convert<hstd::Str> {
    static Node encode(hstd::Str const& str) {
        Node result;
        result = str.toBase();
        return result;
    }
    static bool decode(Node const& in, hstd::Str& out) {
        out = in.as<std::string>();
        return true;
    }
};

template <hstd::IsVariant T, typename CRTP_Derived>
struct variant_convert {
    static bool decode(Node const& value, T& result) {
        CRTP_Derived::init(result, value);
        std::visit(
            [&](auto& variant) {
                ::YAML::convert<typename std::remove_cvref_t<decltype(variant)>>::decode(
                    variant, value);
                return 0;
            },
            result);
    }
};

template <hstd::DescribedRecord T>
struct convert<T> {
    using Bd = boost::describe::describe_bases<T, boost::describe::mod_any_access>;
    using Md = boost::describe::describe_members<T, boost::describe::mod_any_access>;

    static Node encode(T const& str) {
        Node in;
        boost::mp11::mp_for_each<Md>(
            [&](auto const& field) { in[field.name] = str.*field.pointer; });

        boost::mp11::mp_for_each<Bd>([&](auto Base) {
            Node res = ::YAML::convert<typename decltype(Base)::type>::encode(str);
            for (auto const& item : res) {
                in[item.first.as<std::string>()] = item.second;
            }
        });

        return in;
    }

    static bool decode(Node const& in, T& out) {
        boost::mp11::mp_for_each<Md>(
            [&](auto const& field) { out.*field.pointer = in[field.name]; });

        boost::mp11::mp_for_each<Bd>([&](auto Base) {
            ::YAML::convert<typename decltype(Base)::type>::decode(in, out);
        });

        return true;
    }
};
}; // namespace YAML

#pragma once

#include <yaml-cpp/yaml.h>
#include <QString>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/strformat.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <boost/mp11.hpp>

struct BadTypeConversion : public YAML::RepresentationException {
    explicit BadTypeConversion(YAML::Mark mark, const QString& message)
        : YAML::RepresentationException(mark, message.toStdString()) {}
};


using yaml = YAML::Node;

template <typename E>
inline E to_enum(yaml const& in, E fallback) {
    return string_to_enum<E>(in.as<QString>()).value_or(fallback);
}

template <typename T>
inline void maybe_field(yaml const& in, T& out, std::string name) {
    if (in[name]) {
        out = in[name].as<T>();
    }
}

template <typename E>
inline void maybe_enum_field(
    yaml const& in,
    E&          out,
    std::string name,
    E           fallback) {
    if (in[name]) {
        out = to_enum<E>(in[name], fallback);
    }
}

inline QTextStream& operator<<(QTextStream& os, YAML::Node const& value) {
    std::stringstream ss;
    ss << value;
    return os << ss.str();
}

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

template <>
struct convert<QString> {
    static Node encode(QString const& str) {
        Node result;
        result = str.toStdString();
        return result;
    }
    static bool decode(Node const& in, QString& out) {
        out = QString::fromStdString(in.as<std::string>());
        return true;
    }
};


template <IsEnum E>
struct convert<E> {
    static Node encode(E const& str) {
        Node result;
        result = enum_to_string(str).toStdString();
        return result;
    }
    static bool decode(Node const& in, E& out) {
        auto res = enum_serde<E>::from_string(in.as<QString>());
        if (res.has_value()) {
            out = res.value();
            return true;
        } else {
            throw BadTypeConversion(
                in.Mark(),
                "Could not convert $# to $#"
                    % to_string_vec(in, demangle(typeid(E).name())));
        }
    }
};

template <IsVariant T, typename CRTP_Derived>
struct variant_convert {
    static bool decode(Node const& value, T& result) {
        CRTP_Derived::init(result, value);
        std::visit(
            [&](auto& variant) {
                ::YAML::convert<typename std::remove_cvref_t<
                    decltype(variant)>>::decode(variant, value);
                return 0;
            },
            result);
    }
};

template <DescribedRecord T>
struct convert<T> {
    using Bd = boost::describe::
        describe_bases<T, boost::describe::mod_any_access>;
    using Md = boost::describe::
        describe_members<T, boost::describe::mod_any_access>;

    static Node encode(T const& str) {
        Node in;
        boost::mp11::mp_for_each<Md>([&](auto const& field) {
            in[field.name] = str.*field.pointer;
        });

        boost::mp11::mp_for_each<Bd>([&](auto Base) {
            Node res = ::YAML::convert<
                typename decltype(Base)::type>::encode(str);
            for (auto const& item : res) {
                in[item.first.as<std::string>()] = item.second;
            }
        });

        return in;
    }

    static bool decode(Node const& in, T& out) {
        boost::mp11::mp_for_each<Md>([&](auto const& field) {
            out.*field.pointer = in[field.name];
        });

        boost::mp11::mp_for_each<Bd>([&](auto Base) {
            ::YAML::convert<typename decltype(Base)::type>::decode(
                in, out);
        });

        return true;
    }
};
}; // namespace YAML

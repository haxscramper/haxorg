#pragma once

#include <yaml-cpp/yaml.h>
#include <QString>
#include <hstd/system/reflection.hpp>

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
        auto res = string_to_enum<E>(in.as<QString>());
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
}; // namespace YAML

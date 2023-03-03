#pragma once

#include <yaml-cpp/yaml.h>
#include <QString>

using yaml = YAML::Node;

inline QTextStream& operator<<(QTextStream& os, YAML::Node const& value) {
    std::stringstream ss;
    ss << value;
    return os << ss.str();
}

namespace YAML {
template <>
struct convert<QString> {
    static Node encode(QString const& str) {
        Node result;
        result = str.toStdString();
        return result;
    }
    static bool decode(Node const& in, QString& out) {
        out = QString::fromStdString(in.as<std::string>());
    }
};
}; // namespace YAML

#include "Json.hpp"


template class nlohmann::basic_json<>;


QTextStream& operator<<(QTextStream& os, const json& value) {
    std::stringstream ss;
    ss << value;
    os << QString::fromStdString(ss.str());
    return os;
}

QDebug operator<<(QDebug os, const json& value) {
    QDebugStateSaver saved{os};
    return os << to_string(value);
}
QString to_string(const json& j) {
    return QString::fromStdString(nlohmann::to_string(j));
}

void to_json(json& j, CR<Str> str) { to_json(j, str.toBase()); }

void to_json(json& j, CR<QString> str) {
    ns::to_json(j, str.toStdString());
}

void to_json(json& j, int i) { ns::to_json(j, i); }

#pragma once

#include <nlohmann/json.hpp>
#include <QString>
#include <sstream>

#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Vec.hpp>

using json = nlohmann::json;

template <typename T>
inline json to_json(CR<Vec<T>> str) {
    json res = json::array();
    for (const auto& it : str) {
        res.push_back(to_json(it));
    }
    return res;
}

template <typename T>
inline json __jconvert(CR<T> in) {
    json tmp = in;
    return tmp;
}

inline json to_json(CR<std::string> str) { return __jconvert(str); }
inline json to_json(CR<QString> str) { return to_json(str.toStdString()); }
inline json to_json(CR<Str> str) { return to_json(str.toBase()); }

inline void to_json(json& target, CR<QString> str) {
    target = to_json(str);
}

inline QTextStream& operator<<(QTextStream& os, json const& value) {
    std::stringstream ss;
    ss << value;
    os << QString::fromStdString(ss.str());
    return os;
}

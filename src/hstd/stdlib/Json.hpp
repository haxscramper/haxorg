#pragma once

#include <nlohmann/json.hpp>
#include <QString>
#include <sstream>
#include <memory>

#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Opt.hpp>

#include <boost/describe.hpp>

using json   = nlohmann::json;
namespace ns = nlohmann;

extern template class nlohmann::basic_json<>;

void to_json(json& j, int i);
void to_json(json& j, CR<QString> str);
void to_json(json& j, CR<Str> str);

QString      to_string(json const& j);
QDebug       operator<<(QDebug os, json const& value);
QTextStream& operator<<(QTextStream& os, json const& value);

struct JsonFormatOptions {
    int width       = 80;
    int indent      = 2;
    int startIndent = 0;
};

std::string to_compact_json(
    json const&              j,
    JsonFormatOptions const& options = JsonFormatOptions{});

template <typename T>
concept DescribedMembers = boost::describe::has_describe_members<T>::value;


template <typename T>
inline void to_json(json& res, CR<Opt<T>> str);

template <typename T>
inline void to_json(json& res, CR<Vec<T>> str);

template <typename T>
inline void to_json(json& res, std::unique_ptr<T> const& value);

template <DescribedMembers T>
void to_json(json& obj, T const& t) {
    using D1 = boost::describe::
        describe_members<T, boost::describe::mod_public>;
    obj = json::object();
    boost::mp11::mp_for_each<D1>([&](auto D) {
        json tmp;
        to_json(tmp, t.*D.pointer);
        obj[D.name] = tmp;
    });
}

template <typename T>
inline void to_json(json& res, CR<Vec<T>> str) {
    for (const auto& it : str) {
        json tmp;
        to_json(tmp, it);
        res.push_back(tmp);
    }
}


template <typename T>
inline void to_json(json& res, CR<Opt<T>> str) {
    if (str.has_value()) {
        to_json(res, str.value());
    } else {
        res = json();
    }
}

template <typename T>
inline void to_json(json& res, std::unique_ptr<T> const& value) {
    if (value.get() != nullptr) {
        to_json(res, *value);
    } else {
        res = json();
    }
}

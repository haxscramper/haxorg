#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <sstream>
#include <memory>

#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Opt.hpp>

#include <boost/describe.hpp>
#include <hstd/system/reflection.hpp>

using json   = nlohmann::json;
namespace ns = nlohmann;

extern template class nlohmann::basic_json<>;

void to_json(json& j, int i);
void to_json(json& j, CR<std::string> str);
void to_json(json& j, CR<Str> str);
void from_json(const json& in, std::string& out);
void from_json(const json& in, int& out);
void from_json(const json& in, bool& out);

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

template <DescribedEnum E>
void from_json(json const& j, E& str) {
    Opt<E> value = enum_serde<E>::from_string(j.get<std::string>());
    if (value) {
        str = value.value();
    } else {
        throw json::type_error::create(
            302,
            "Could not convert json value <" + j.dump()
                + "> to enum for type " + typeid(E).name(),
            nullptr);
    }
}

template <typename T>
void from_json(json const& json, Opt<T>& value) {
    value = SerdeDefaultProvider<T>::get();
    from_json(json, *value);
}


template <DescribedRecord T>
static void to_json(json& j, const T& str) {
    using Bd = boost::describe::
        describe_bases<T, boost::describe::mod_any_access>;
    using Md = boost::describe::
        describe_members<T, boost::describe::mod_any_access>;

    if (!j.is_object()) { j = json::object(); }

    boost::mp11::mp_for_each<Md>(
        [&](auto const& field) { j[field.name] = str.*field.pointer; });

    boost::mp11::mp_for_each<Bd>([&](auto Base) {
        to_json<typename decltype(Base)::type>(j, str);
    });
}

template <DescribedRecord T>
void from_json(const json& in, T& out) {
    using Bd = boost::describe::
        describe_bases<T, boost::describe::mod_any_access>;
    using Md = boost::describe::
        describe_members<T, boost::describe::mod_any_access>;
    boost::mp11::mp_for_each<Md>([&](auto const& field) {
        if (in.contains(field.name)) {
            from_json(in[field.name], out.*field.pointer);
        }
    });

    boost::mp11::mp_for_each<Bd>([&](auto Base) {
        from_json<std::remove_cvref_t<typename decltype(Base)::type>>(
            in, out);
    });
}

template <typename T>
void from_json(const json& in, Vec<T>& out) {
    for (auto const& j : in) {
        T tmp;
        from_json(j, tmp);
        out.push_back(tmp);
    }
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
inline void to_json(json& res, CR<std::vector<T>> str) {
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

void filterFields(json& j, const std::vector<std::string>& fieldsToRemove);

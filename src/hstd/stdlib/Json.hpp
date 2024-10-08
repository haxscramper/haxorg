#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <memory>

#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Opt.hpp>

#include <boost/describe.hpp>
#include <hstd/system/reflection.hpp>

using json   = nlohmann::json;
namespace ns = nlohmann;

extern template class nlohmann::basic_json<>;

template <typename T>
struct JsonSerde;

template <>
struct JsonSerde<int> {
    static json to_json(int const& it) { return json(it); }
    static int  from_json(json const& j) { return j.get<int>(); }
};

template <>
struct JsonSerde<unsigned int> {
    static json to_json(unsigned int const& it) { return json(it); }
    static unsigned int from_json(json const& j) {
        return j.get<unsigned int>();
    }
};

template <>
struct JsonSerde<unsigned long> {
    static json to_json(unsigned long const& it) { return json(it); }
    static unsigned long from_json(json const& j) {
        return j.get<unsigned long>();
    }
};

template <>
struct JsonSerde<unsigned long long> {
    static json to_json(unsigned long long const& it) { return json(it); }
    static unsigned long long from_json(json const& j) {
        return j.get<unsigned long long>();
    }
};

template <>
struct JsonSerde<float> {
    static json  to_json(float const& it) { return json(it); }
    static float from_json(json const& j) { return j.get<float>(); }
};

template <>
struct JsonSerde<std::string> {
    static json        to_json(std::string const& it) { return json(it); }
    static std::string from_json(json const& j) {
        return j.get<std::string>();
    }
};

template <>
struct JsonSerde<char const*> {
    static json        to_json(char const* const& it) { return json(it); }
    static char const* from_json(json const& j) { return nullptr; }
};


template <>
struct JsonSerde<Str> {
    static json to_json(Str const& it) { return json(it.toBase()); }
    static Str  from_json(json const& j) { return j.get<std::string>(); }
};


template <>
struct JsonSerde<bool> {
    static json to_json(bool const& it) { return json(it); }
    static bool from_json(json const& j) { return j.get<bool>(); }
};

template <>
struct JsonSerde<json> {
    static json to_json(json const& it) { return it; }
    static json from_json(json const& j) { return j; }
};


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
struct JsonSerde<std::vector<T>> {
    static json to_json(std::vector<T> const& it) {
        auto result = json::array();
        for (auto const& i : it) {
            result.push_back(JsonSerde<T>::to_json(i));
        }

        return result;
    }
    static std::vector<T> from_json(json const& j) {
        std::vector<T> result;
        for (auto const& i : j) {
            result.push_back(JsonSerde<T>::from_json(i));
        }
        return result;
    }
};


template <typename K, typename V>
struct JsonSerde<std::unordered_map<K, V>> {
    static json to_json(std::unordered_map<K, V> const& it) {
        auto result = json::array();
        for (auto const& [key, val] : it) {
            result.push_back(json::object({
                {"key", JsonSerde<K>::to_json(key)},
                {"value", JsonSerde<V>::to_json(val)},
            }));
        }

        return result;
    }
    static std::unordered_map<K, V> from_json(json const& j) {
        std::unordered_map<K, V> result;
        for (auto const& i : j) {
            result[JsonSerde<K>::from_json(i["key"])] = JsonSerde<
                V>::from_json(i["value"]);
        }
        return result;
    }
};

template <typename V>
struct JsonSerde<std::unordered_map<std::string, V>> {
    static json to_json(std::unordered_map<std::string, V> const& it) {
        auto result = json::object();
        for (auto const& [key, val] : it) {
            result[key] = JsonSerde<V>::to_json(val);
        }

        return result;
    }
    static std::unordered_map<std::string, V> from_json(json const& j) {
        std::unordered_map<std::string, V> result;
        for (auto const& [key, value] : j.items()) {
            result[key] = JsonSerde<V>::from_json(value);
        }
        return result;
    }
};


template <typename T>
struct JsonSerde<Vec<T>> {
    static json to_json(Vec<T> const& it) {
        auto result = json::array();
        for (auto const& i : it) {
            result.push_back(JsonSerde<T>::to_json(i));
        }

        return result;
    }
    static Vec<T> from_json(json const& j) {
        Vec<T> result;
        for (auto const& i : j) {
            result.push_back(JsonSerde<T>::from_json(i));
        }
        return result;
    }
};

template <typename T>
struct JsonSerde<std::unique_ptr<T>> {
    static json to_json(std::unique_ptr<T> const& it) {
        if (it.get() == nullptr) {
            return json();
        } else {
            return JsonSerde<T>::to_json(*it);
        }
    }
    static std::unique_ptr<T> from_json(json const& j) {
        if (j.is_null()) {
            return nullptr;
        } else {
            return std::make_unique<T>(JsonSerde<T>::from_json(j));
        }
    }
};

template <typename T>
struct JsonSerde<std::shared_ptr<T>> {
    static json to_json(std::shared_ptr<T> const& it) {
        if (it.get() == nullptr) {
            return json();
        } else {
            return JsonSerde<T>::to_json(*it);
        }
    }
    static std::shared_ptr<T> from_json(json const& j) {
        if (j.is_null()) {
            return nullptr;
        } else {
            return std::make_shared<T>(JsonSerde<T>::from_json(j));
        }
    }
};


template <typename T>
struct JsonSerde<std::optional<T>> {
    static json to_json(std::optional<T> const& it) {
        if (it) {
            return JsonSerde<T>::to_json(*it);
        } else {
            return json();
        }
    }
    static std::optional<T> from_json(json const& j) {
        if (j.is_null()) {
            return std::nullopt;
        } else {
            return std::make_optional<T>(JsonSerde<T>::from_json(j));
        }
    }
};

template <DescribedRecord T>
struct JsonSerdeDescribedRecordBase {
    static json to_json(T const& obj) {
        json result = json::object();

        for_each_field_with_bases<T>([&](auto const& field) {
            result[field.name] = JsonSerde<
                std::remove_cvref_t<decltype(obj.*field.pointer)>>::
                to_json(obj.*field.pointer);
        });

        return result;
    }

    static T from_json(json const& j) {
        T result = SerdeDefaultProvider<T>::get();
        for_each_field_with_bases<T>([&](auto const& field) {
            if (j.contains(field.name)) {
                result.*field.pointer = JsonSerde<
                    std::remove_cvref_t<decltype(result.*field.pointer)>>::
                    from_json(j[field.name]);
            }
        });

        return result;
    }
};

template <DescribedRecord T>
struct JsonSerde<T> : JsonSerdeDescribedRecordBase<T> {};


template <DescribedEnum E>
struct JsonSerde<E> {
    static E from_json(json const& j) {
        Opt<E> value = enum_serde<E>::from_string(j.get<std::string>());
        if (value) {
            return value.value();
        } else {
            throw json::type_error::create(
                302,
                "Could not convert json value <" + j.dump()
                    + "> to enum for type " +
#ifdef __cpp_rtti
                    typeid(E).name()
#else
                    ""
#endif
                    ,
                nullptr);
        }
    }

    static json to_json(E value) {
        return enum_serde<E>::to_string(value);
    }
};

void filterFields(json& j, const std::vector<std::string>& fieldsToRemove);

template <typename T>
json to_json_eval(T const& val) {
    return JsonSerde<T>::to_json(val);
}

template <typename T>
void from_json_eval(json const& j, T& out_value) {
    out_value = JsonSerde<T>::from_json(j);
}


template <typename T>
T from_json_eval(json const& j) {
    return JsonSerde<T>::from_json(j);
}

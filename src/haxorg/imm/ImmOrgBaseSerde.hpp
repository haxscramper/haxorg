#pragma once 

#include <haxorg/imm/ImmOrgBase.hpp>


template <>
struct hstd::JsonSerde<org::imm::ImmAdapter> {
    static json to_json(org::imm::ImmAdapter const& it) {
        return json(it.id.getReadableId());
    }
    static org::imm::ImmAdapter from_json(json const& j) {
        throw logic_assertion_error::init(
            "org::ImmAdapter does not support deserialization.");
    }
};

template <typename T>
struct hstd::JsonSerde<org::imm::ImmAdapterT<T>> {
    static json to_json(org::imm::ImmAdapterT<T> const& it) {
        return json(it.id.getReadableId());
    }
    static org::imm::ImmAdapterT<T> from_json(json const& j) {
        throw logic_assertion_error::init(
            "org::ImmAdapterT<T> does not support deserialization.");
    }
};

template <typename T>
struct hstd::JsonSerde<hstd::ext::ImmBox<T>> {
    static json to_json(hstd::ext::ImmBox<T> const& it) {
        return JsonSerde<T>::to_json(it.get());
    }
    static hstd::ext::ImmBox<T> from_json(json const& j) {
        return hstd::ext::ImmBox<T>{JsonSerde<T>::from_json(j)};
    }
};

template <typename T>
struct hstd::JsonSerde<hstd::ext::ImmVec<T>> {
    static json to_json(hstd::ext::ImmVec<T> const& it) {
        auto result = json::array();
        for (auto const& i : it) {
            result.push_back(JsonSerde<T>::to_json(i));
        }

        return result;
    }
    static hstd::ext::ImmVec<T> from_json(json const& j) {
        hstd::ext::ImmVec<T> result;
        auto                 tmp = result.transient();
        for (auto const& i : j) {
            tmp.push_back(JsonSerde<T>::from_json(i));
        }
        return tmp.persistent();
    }
};

template <typename T>
struct hstd::JsonSerde<hstd::ext::ImmSet<T>> {
    static json to_json(hstd::ext::ImmSet<T> const& it) {
        auto result = json::array();
        for (auto const& i : it) {
            result.push_back(JsonSerde<T>::to_json(i));
        }

        return result;
    }
    static hstd::ext::ImmSet<T> from_json(json const& j) {
        hstd::ext::ImmSet<T> result;
        auto                 tmp = result.transient();
        for (auto const& i : j) {
            result.insert(JsonSerde<T>::from_json(i));
        }
        return tmp.persistent();
    }
};

template <typename K, typename V>
struct hstd::JsonSerde<immer::map<K, V>> {
    static json to_json(immer::map<K, V> const& it) {
        auto result = json::array();
        for (auto const& [key, val] : it) {
            result.push_back(json::object({
                {"key", JsonSerde<K>::to_json(key)},
                {"value", JsonSerde<V>::to_json(val)},
            }));
        }

        return result;
    }
    static immer::map<K, V> from_json(json const& j) {
        immer::map<K, V> result;
        auto             tmp = result.transient();
        for (auto const& i : j) {
            result.insert(
                JsonSerde<K>::from_json(i["key"]),
                JsonSerde<V>::from_json(i["value"]));
        }
        return tmp.persistent();
    }
};

template <typename K, typename V>
struct hstd::JsonSerde<hstd::ext::ImmMap<K, V>> {
    static json to_json(hstd::ext::ImmMap<K, V> const& it) {
        return JsonSerde<immer::map<K, V>>::to_json(it);
    }
    static hstd::ext::ImmMap<K, V> from_json(json const& j) {
        return JsonSerde<immer::map<K, V>>::from_json(j);
    }
};

template <>
struct hstd::JsonSerde<org::imm::ImmId> {
    static json to_json(org::imm::ImmId const& it) {
        return json::object(
            {{"number", it.getValue()}, {"format", it.getReadableId()}});
    }
    static org::imm::ImmId from_json(json const& j) {
        return org::imm::ImmId::FromValue(
            j["number"].get<unsigned long long>());
    }
};

template <typename T>
struct hstd::JsonSerde<org::imm::ImmIdT<T>> {
    static json to_json(org::imm::ImmIdT<T> const& it) {
        return JsonSerde<org::imm::ImmId>::to_json(it.toId());
    }
    static org::imm::ImmIdT<T> from_json(json const& j) {
        return org::imm::ImmIdT<T>{
            JsonSerde<org::imm::ImmId>::from_json(j)};
    }
};

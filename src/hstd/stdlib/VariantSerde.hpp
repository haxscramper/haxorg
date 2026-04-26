#pragma once

#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/JsonUse.hpp>
#include <hstd/stdlib/JsonSerde.hpp>

namespace hstd {

template <IsVariant V>
struct JsonSerde<V> {
    static json to_json(V const& it) {
        auto result     = json::object();
        result["index"] = JsonSerde<int>::to_json(it.index());
        std::visit(
            [&]<typename T>(T const& value) {
                result["value"] = JsonSerde<T>::to_json(value);
            },
            it);

        return result;
    }
    static V from_json(json const& j) {
        V result = variant_from_index<V>(j["index"].get<int>());
        std::visit(
            [&]<typename T>(T& value) {
                value = JsonSerde<T>::from_json(j["value"]);
            },
            result);
    }
};


template <typename V>
    requires DescribedRecord<V> && IsSubVariantType<V>
struct JsonSerde<V> : JsonSerdeDescribedRecordBase<V> {
    // Only override the variant type `kind` serialization, the field
    // `.data` is exported as a variant with its own `.index` field, so
    // loading is not changed.
    static json to_json(V const& it) {
        auto result = JsonSerdeDescribedRecordBase<V>::to_json(it);
        result[V::sub_variant_get_enum_name()] = JsonSerde<
            typename V::variant_enum_type>::
            to_json(it.sub_variant_get_kind());
        return result;
    }
};

} // namespace hstd

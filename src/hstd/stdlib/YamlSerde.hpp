#pragma once 

#include <hstd/stdlib/JsonSerde.hpp>
#include <hstd/stdlib/Yaml.hpp>

template <>
struct hstd::JsonSerde<YAML::Mark> {
    static YAML::Mark from_json(json const& j) {
        auto res   = YAML::Mark();
        res.line   = JsonSerde<int>::from_json(j["line"]);
        res.column = JsonSerde<int>::from_json(j["column"]);
        res.pos    = JsonSerde<int>::from_json(j["pos"]);
        return res;
    }

    static json to_json(YAML::Mark const& value) {
        return json::object({
            {"line", JsonSerde<int>::to_json(value.line)},
            {"column", JsonSerde<int>::to_json(value.column)},
            {"pos", JsonSerde<int>::to_json(value.pos)},
        });
    }
};

template <>
struct hstd::JsonSerde<YAML::Node> {
    static YAML::Node from_json(json const& j) {
        return org::test::toYaml(j);
    }
    static json to_json(YAML::Node const& j) {
        return org::test::toJson(j);
    }
};

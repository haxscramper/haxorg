#pragma once

#include <yaml-cpp/yaml.h>

#include <lexbase/Node.hpp>
#include <lexbase/Token.hpp>

struct ParseSpecFile {
    Opt<YAML::Node>      expected;
    Opt<Vec<YAML::Node>> tokens;
    Str                  source;

    /// Name of the method to call for lexing or parsing. Pointer to
    /// implementation is resolved externally, spec file just contains the
    /// required name.
    Opt<Str> lexImplName;
    Opt<Str> parseImplName;

    struct SpecValidationError : public std::runtime_error {
        explicit SpecValidationError(const std::string& message)
            : std::runtime_error(message) {}
    };


    enum class ExpectedMode
    {
        Flat,
        Nested,
        Named
    };

    BOOST_DESCRIBE_NESTED_ENUM(ExpectedMode, Flat, Nested, Named);

    ExpectedMode expectedMode;

    ParseSpecFile(CR<YAML::Node> node) {
        if (node["source"]) {
            source = node["source"].as<std::string>();
        } else {
            throw SpecValidationError(
                "Input spec must contain 'source' string field");
        }


        if (node["expected"]) {
            expectedMode = string_to_enum<ExpectedMode>(
                               node["expected"].as<std::string>())
                               .value_or(ExpectedMode::Nested);
        }
    }

    template <typename N, typename K>
    NodeGroup<N, K> getNodeGroup() {
        NodeGroup<N, K> result;

        return result;
    }

    template <typename K>
    TokenGroup<K> getTokenGroup() {
        TokenGroup<K> result;

        return result;
    }
};

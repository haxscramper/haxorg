#pragma once

#include <yaml-cpp/yaml.h>

#include <lexbase/Node.hpp>
#include <lexbase/Token.hpp>

struct ParseSpec {
    Opt<YAML::Node> subnodes;
    Opt<YAML::Node> tokens;
    Str             source;

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

    ExpectedMode expectedMode = ExpectedMode::Nested;

    ParseSpec(CR<YAML::Node> node) {
        if (node["lex"]) {
            lexImplName = node["lex"].as<std::string>();
        }
        if (node["parse"]) {
            parseImplName = node["parse"].as<std::string>();
        }

        if (node["source"]) {
            source = node["source"].as<std::string>();
        } else {
            throw SpecValidationError(
                "Input spec must contain 'source' string field");
        }

        if (node["subnodes"]) {
            subnodes = node["subnodes"];
        }

        if (node["tokens"]) {
            tokens = node["tokens"];
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

struct ParseSpecGroup {
    ParseSpecGroup(CR<YAML::Node> node) {
        if (node["items"]) {
            if (node["items"].IsSequence()) {
                for (const auto& it : node["items"]) {
                    auto spec = ParseSpec(it);

                    if (!spec.lexImplName && node["lex"]) {
                        spec.lexImplName = node["lex"].as<std::string>();
                    }

                    if (!spec.parseImplName && node["parse"]) {
                        spec.parseImplName = node["parse"]
                                                 .as<std::string>();
                    }

                    if (!it["expected"] && node["expected"]) {
                        spec.expectedMode =
                            //
                            string_to_enum<ParseSpec::ExpectedMode>(
                                node["expected"].as<std::string>())
                                .value_or(ParseSpec::ExpectedMode::Nested);
                    }

                    specs.push_back(spec);
                }
            } else {
                throw ParseSpec::SpecValidationError(
                    "Spec group 'items' field must be a sequence");
            }

        } else {
            specs.push_back(ParseSpec(node));
        }
    }

    Vec<ParseSpec> specs;
};

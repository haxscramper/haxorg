#pragma once

#include <yaml-cpp/yaml.h>

#include <lexbase/Node.hpp>
#include <lexbase/Token.hpp>

struct ParseSpec {
    Opt<YAML::Node> subnodes;
    Opt<YAML::Node> tokens;
    Str             source;
    Opt<QString>    testName;

    struct Dbg {
        bool traceLex    = false;
        bool traceParse  = false;
        bool lexToFile   = false;
        bool parseToFile = false;
        bool printLexed  = false;
        bool printParsed = false;
    };

    Dbg dbg;


    /// Name of the method to call for lexing or parsing. Pointer to
    /// implementation is resolved externally, spec file just contains the
    /// required name.
    Opt<Str> lexImplName;
    Opt<Str> parseImplName;

    struct SpecValidationError : public std::runtime_error {
        explicit SpecValidationError(const QString& message)
            : std::runtime_error(message.toStdString()) {}
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
        if (node["debug"]) {
            auto debug = node["debug"];
            if (debug["trace_lex"]) {
                dbg.traceLex = debug["trace_lex"].as<bool>();
            }

            if (debug["trace_parse"]) {
                dbg.traceParse = debug["trace_parse"].as<bool>();
            }

            if (debug["lex_to_file"]) {
                dbg.lexToFile = debug["lex_to_file"].as<bool>();
            }

            if (debug["parse_to_file"]) {
                dbg.parseToFile = debug["parse_to_file"].as<bool>();
            }

            if (debug["print_lexed"]) {
                dbg.printLexed = debug["print_lexed"].as<bool>();
            }

            if (debug["print_parsed"]) {
                dbg.printLexed = debug["print_parsed"].as<bool>();
            }
        }

        if (node["lex"]) {
            lexImplName = node["lex"].as<QString>();
        }

        if (node["name"]) {
            testName = node["name"].as<QString>();
        }

        if (node["parse"]) {
            parseImplName = node["parse"].as<QString>();
        }

        if (node["source"]) {
            source = node["source"].as<QString>();
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
                               node["expected"].as<QString>())
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
                        spec.lexImplName = node["lex"].as<QString>();
                    }

                    if (!spec.parseImplName && node["parse"]) {
                        spec.parseImplName = node["parse"].as<QString>();
                    }

                    if (!spec.testName) {
                        if (node["name"]) {
                            spec.testName = node["name"].as<QString>();
                        } else {
                        }
                    }

                    if (!it["expected"] && node["expected"]) {
                        spec.expectedMode =
                            //
                            string_to_enum<ParseSpec::ExpectedMode>(
                                node["expected"].as<QString>())
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

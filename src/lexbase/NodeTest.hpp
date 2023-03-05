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
        bool traceLex          = false;
        bool traceParse        = false;
        bool lexToFile         = false;
        bool parseToFile       = false;
        bool printLexed        = false;
        bool printParsed       = false;
        bool printSource       = false;
        bool doParse           = true;
        bool doLex             = true;
        bool printLexedToFile  = false;
        bool printParsedToFile = false;
    };

    Dbg dbg;


    /// Name of the method to call for lexing or parsing. Pointer to
    /// implementation is resolved externally, spec file just contains the
    /// required name.
    Str lexImplName;
    Str parseImplName;

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
            auto opt   = [&](bool& target, std::string name) {
                if (debug[name]) {
                    target = debug[name].as<bool>();
                }
            };

            opt(dbg.traceLex, "trace_lex");
            opt(dbg.doParse, "do_lex");
            opt(dbg.doParse, "do_parse");
            opt(dbg.traceParse, "trace_parse");
            opt(dbg.lexToFile, "lex_to_file");
            opt(dbg.parseToFile, "parse_to_file");
            opt(dbg.printLexed, "print_lexed");
            opt(dbg.printParsed, "print_parsed");
            opt(dbg.printLexedToFile, "print_lexed_to_file");
            opt(dbg.printParsedToFile, "print_parsed_to_file");
            opt(dbg.printSource, "print_source");
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
    ParseSpecGroup(CR<YAML::Node> node, CR<QString> from) {
        auto validate = [&](CR<ParseSpec> spec) {
            if (spec.parseImplName.empty() || spec.lexImplName.empty()) {
                throw ParseSpec::SpecValidationError(
                    "$# function name missing from specifiction "
                    "-- must be provided as `$#` in either "
                    "specific parser test case on toplevel of the "
                    "test file or in specific test in $#"
                    % to_string_vec(
                        spec.parseImplName.empty() ? "Parser" : "Lexer",
                        spec.parseImplName.empty() ? "lex" : "parse",
                        from));
            }
        };
        if (node["items"]) {
            if (node["items"].IsSequence()) {
                for (const auto& it : node["items"]) {
                    auto spec = ParseSpec(it);

                    if (spec.lexImplName.empty() && node["lex"]) {
                        spec.lexImplName = node["lex"].as<QString>();
                    }

                    if (spec.parseImplName.empty() && node["parse"]) {
                        spec.parseImplName = node["parse"].as<QString>();
                    }

                    validate(spec);

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
            auto tmp = ParseSpec(node);
            validate(tmp);
            specs.push_back(tmp);
        }
    }

    Vec<ParseSpec> specs;
};

#pragma once


#include <lexbase/Node.hpp>
#include <lexbase/Token.hpp>

#include <hstd/stdlib/Yaml.hpp>
#include <hstd/stdlib/Json.hpp>

struct ParseSpec {
    Opt<yaml>    subnodes;
    Opt<yaml>    tokens;
    Opt<json>    semExpected;
    Str          source;
    Opt<QString> testName;
    YAML::Mark   specLocation;
    YAML::Mark   sourceLocation;


    struct Conf {
        enum class MatchMode
        {
            Full,
            ExpectedSubset
        };

        MatchMode tokenMatchMode = MatchMode::Full;
        MatchMode nodeMatchMode  = MatchMode::Full;
        BOOST_DESCRIBE_NESTED_ENUM(MatchMode, Full, ExpectedSubset);
    };

    Conf conf;

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
        bool printSemToFile    = false;
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

    ParseSpec(CR<yaml> node);

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
    ParseSpecGroup(CR<yaml> node, CR<QString> from);

    Vec<ParseSpec> specs;
};

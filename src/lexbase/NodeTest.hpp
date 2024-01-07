#pragma once

#include <lexbase/Node.hpp>
#include <lexbase/Token.hpp>

#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/Yaml.hpp>
#include <hstd/system/macros.hpp>
#include <hstd/stdlib/Filesystem.hpp>


json toJson(CR<yaml> node);

struct ParseSpec {
    std::string getLocMsg() const {
        return "$# at $#:$#"
             % to_string_vec(
                   name ? *name : "<test>", specFile, specLocation.line);
    }

    struct Conf {
        DECL_DESCRIBED_ENUM(MatchMode, Full, ExpectedSubset);
        DECL_FIELDS(
            Conf,
            (),
            ((MatchMode), tokenMatch, MatchMode::Full),
            ((MatchMode), nodeMatch, MatchMode::Full));
    };


    struct Dbg {
        DECL_FIELDS(
            Dbg,
            (),
            /// Do trace for lex/parse/sem
            ((bool), traceLex, false),
            ((bool), traceParse, false),
            ((bool), traceSem, false),
            /// Output trace to the file
            ((bool), lexToFile, false),
            ((bool), parseToFile, false),
            ((bool), semToFile, false),
            /// Print lex/parse/sem/source values for processing
            ((bool), printLexed, false),
            ((bool), printBaseLexed, false),
            ((bool), printParsed, false),
            ((bool), printSem, false),
            ((bool), printSource, false),
            /// Test should run lex/parse/sem stages
            ((bool), doParse, true),
            ((bool), doLex, true),
            ((bool), doSem, true),
            /// Print sem/lex/parse output debug information to the file
            ((bool), printLexedToFile, false),
            ((bool), printBaseLexedToFile, false),
            ((bool), printParsedToFile, false),
            ((bool), printSemToFile, false),
            /// directory to write debug files to
            ((std::string), debugOutDir, ""));
    };

    struct ExporterExpect {
        DECL_FIELDS(
            ExporterExpect,
            (),
            ((std::string), name, ""),
            /// Optional parameters to pass to the exporter run.
            ((Opt<yaml>), parmeters, std::nullopt),
            ((yaml), expected, yaml()),
            ((bool), print, false),
            ((bool), printToFile, false),
            /// Print additional trace logs for exporter in the debug
            /// directory for parent test?
            ((bool), doTrace, false));
    };

    fs::path debugFile(std::string relativePath, bool create = true) const;

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

    ParseSpec(
        CR<yaml>        node,
        CR<std::string> specFile,
        CR<std::string> testRoot);

    template <typename N, typename K, typename V>
    NodeGroup<N, K, V> getNodeGroup() {
        NodeGroup<N, K, V> result;

        return result;
    }

    template <typename K, typename V>
    TokenGroup<K, V> getTokenGroup() {
        TokenGroup<K, V> result;

        return result;
    }

  public:
    DECL_FIELDS(
        ParseSpec,
        (),
        ((ExpectedMode), expectedMode, ExpectedMode::Nested),
        /// List of exporter executions along with the additional
        /// parameters to supply to the exporter. Specific handling of
        /// different exporter variations is implemented in the corpus
        /// file.
        ((Vec<ExporterExpect>), exporters, {}),
        /// Name of the method to call for lexing or parsing. Pointer to
        /// implementation is resolved externally, spec file just contains
        /// the required name.
        ((Opt<std::string>), file, std::nullopt),
        ((Dbg), debug, Dbg{}),
        ((Conf), conf, Conf{}),
        ((Opt<yaml>), subnodes, std::nullopt),
        ((Opt<yaml>), base_tokens, std::nullopt),
        ((Opt<yaml>), tokens, std::nullopt),
        ((Opt<json>), sem, std::nullopt),
        ((Str), source, ""),
        ((Opt<std::string>), name, std::nullopt),
        ((YAML::Mark), specLocation, YAML::Mark()),
        ((YAML::Mark), sourceLocation, YAML::Mark()),
        ((std::string), specFile, ""), );
};

struct ParseSpecGroup {
    ParseSpecGroup(
        CR<yaml>        node,
        CR<std::string> from,
        CR<std::string> testRoot);

    Vec<ParseSpec> specs;
};

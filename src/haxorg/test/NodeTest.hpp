#pragma once

#include <haxorg/lexbase/Node.hpp>
#include <haxorg/lexbase/Token.hpp>

#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/Yaml.hpp>
#include <hstd/system/macros.hpp>
#include <hstd/stdlib/Filesystem.hpp>


json toJson(CR<yaml> node);
yaml toYaml(CR<json> node);

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

    /// `debug:` field in the yaml specification. All the fields in the
    /// YAML are directly mapped to the parse spec debug configuration.
    ///
    /// ```yaml
    /// - name: "Call named command"
    ///   debug:
    ///   doLex: false
    /// ```
    struct Dbg {
        /// Enable file-based tracing for all steps of the spec
        /// checking
        bool traceAll = false;
        /// Trace execution of the re/flex lexer
        bool traceLex = false;
        /// Trace conversion from base token list to the regrouped
        /// tokens
        bool traceLexBase = false;
        /// Tracing of converted token stream to DOD org-mode tree
        bool traceParse = false;
        /// Conversion of the tree to the
        bool traceSem = false;
        /// Print lex/parse/sem/source values for processing
        bool printLexed     = false;
        bool printBaseLexed = false;
        bool printParsed    = false;
        bool printSem       = false;
        bool printSource    = false;
        /// Test should run lex/parse/sem stages
        bool doParse   = true;
        bool doLex     = true;
        bool doLexBase = true;
        bool doSem     = true;

        /// If the initial sem stage completed without issues, format
        /// the document to string and then parse it again, comparing
        /// parsed tree V1 vs parsed tree V2
        bool doFormatReparse = true;
        /// Compare flat DOD nodes generated in the first and the
        /// second run of the parsed content. Comparison is done using
        /// simplified versions of the flat trees -- remove
        /// `org::Empty` nodes, newlines and whitespaces, to avoid too
        /// making the test corpus too brittle.
        bool doFlatParseCompare = true;
        /// Print sem/lex/parse output debug information to the file
        bool printLexedToFile       = false;
        bool printBaseLexedToFile   = false;
        bool printParsedToFile      = false;
        bool printSemToFile         = false;
        int  maxBaseLexUnknownCount = 100;
        /// directory to write debug files to
        std::string debugOutDir = "";

        DESC_FIELDS(
            Dbg,
            (traceAll,
             traceLex,
             traceLexBase,
             traceParse,
             traceSem,
             printLexed,
             printBaseLexed,
             printParsed,
             printSem,
             printSource,
             doParse,
             doLex,
             doLexBase,
             doSem,
             doFormatReparse,
             doFlatParseCompare,
             printLexedToFile,
             printBaseLexedToFile,
             printParsedToFile,
             printSemToFile,
             maxBaseLexUnknownCount,
             debugOutDir));
    };

    fs::path debugFile(
        std::string     relativePath,
        CR<std::string> relDebug,
        bool            create = true) const;

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

    ParseSpec() {}

    static ParseSpec FromSource(std::string&& context) {
        ParseSpec spec;
        spec.source = std::move(context);
        spec.name   = "<source>";
        return spec;
    }

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
    ExpectedMode expectedMode = ExpectedMode::Nested;
    /// Name of the method to call for lexing or parsing. Pointer to
    /// implementation is resolved externally, spec file just contains
    /// the required name.
    Opt<std::string> file           = std::nullopt;
    Dbg              debug          = Dbg{};
    Conf             conf           = Conf{};
    Opt<yaml>        subnodes       = std::nullopt;
    Opt<yaml>        base_tokens    = std::nullopt;
    Opt<yaml>        tokens         = std::nullopt;
    Opt<json>        sem            = std::nullopt;
    Str              source         = "";
    Opt<std::string> name           = std::nullopt;
    YAML::Mark       specLocation   = YAML::Mark();
    YAML::Mark       sourceLocation = YAML::Mark();
    std::string      specFile       = "";
    /// \brief Spec tags for filtering the groups of tests in pytest. In
    /// the `.yaml` file they are specified as `["tag"]`, when rendered for
    /// pytest they can be checked for as `test_gtest_tag("tag")`
    Vec<std::string> tags = {};

    DESC_FIELDS(
        ParseSpec,
        (expectedMode,
         file,
         debug,
         conf,
         subnodes,
         base_tokens,
         tokens,
         sem,
         source,
         name,
         specLocation,
         sourceLocation,
         tags,
         specFile));
};

struct ParseSpecGroup {
    ParseSpecGroup(
        CR<yaml>        node,
        CR<std::string> from,
        CR<std::string> testRoot);

    Vec<ParseSpec> specs;
};

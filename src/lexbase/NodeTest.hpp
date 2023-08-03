#pragma once

#include <lexbase/Node.hpp>
#include <lexbase/Token.hpp>

#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/Yaml.hpp>


#define __define_field_aux(first, second, third)                          \
    __unpack_pars first second = third;

#define __per_field(class_bases_bases, field) __define_field(field)

#define __get_field_name_aux(a, fieldName, d) fieldName
#define __get_field_name(_, arg) , __get_field_name_aux arg
#define __drop_leading_comma(first, ...) __VA_ARGS__

#define __define_field(arg) __define_field_aux arg
#define __define_field_only(_, arg) __define_field_aux arg

#define __pass_args_field_aux(_1, fieldname, _3) fieldname(args.fieldname),
#define __pass_args_field(_, arg) __pass_args_field_aux arg

#define EMPTY()

#define DECL_FIELDS(classname, bases, ...)                                \
    FOR_EACH_CALL_WITH_PASS(__per_field, (classname, bases), __VA_ARGS__) \
                                                                          \
    BOOST_DESCRIBE_CLASS(                                                 \
        classname,                                                        \
        bases, /* Expand teh list of fields and leave only the the name   \
    of the field to be passed to the public members of the                \
    boost describe */                                                     \
        (      /* < Extra wrapping paren, __get_field_name leaves out the \
      a,b,c,d,e list*/                                                    \
         __drop_leading_comma EMPTY()(EXPAND(FOR_EACH_CALL_WITH_PASS(     \
             __get_field_name,                                            \
             () /* < Nothing to pass around */,                           \
             __VA_ARGS__)))),                                             \
        () /* For simplicity reasons, sem nodes have public fields and no \
              protected/private members */                                \
        ,                                                                 \
        ());

struct ParseSpec {
    Opt<yaml>    subnodes;
    Opt<yaml>    tokens;
    Opt<json>    semExpected;
    Str          source;
    Opt<QString> testName;
    YAML::Mark   specLocation;
    YAML::Mark   sourceLocation;
    QString      specFile;

    QString getLocMsg() const {
        return "$# at $#:$#"
             % to_string_vec(
                   testName ? *testName : "<test>",
                   specFile,
                   specLocation.line);
    }

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
        DECL_FIELDS(
            Dbg,
            (),
            ((bool), traceLex, false),
            ((bool), traceParse, false),
            ((bool), traceSem, false),
            ((bool), lexToFile, false),
            ((bool), parseToFile, false),
            ((bool), semToFile, false),
            ((bool), printLexed, false),
            ((bool), printParsed, false),
            ((bool), printSource, false),
            /// Test should run lex/parse/sem stages
            ((bool), doParse, true),
            ((bool), doLex, true),
            ((bool), doSem, true),
            /// Print sem/lex/parse output debug information to the file
            ((bool), printLexedToFile, false),
            ((bool), printParsedToFile, false),
            ((bool), printSemToFile, false),
            /// directory to write debug files to
            ((QString), debugOutDir, ""));
    };

    struct ExporterExpect {
        DECL_FIELDS(
            ExporterExpect,
            (),
            ((QString), exporterName, ""),
            /// Optional parameters to pass to the exporter run.
            ((Opt<yaml>), parmeters, std::nullopt),
            ((yaml), expected, yaml()),
            /// Print additional trace logs for exporter in the debug
            /// directory for parent test?
            ((bool), traceExport, false));
    };

    /// List of exporter executions along with the additional parameters to
    /// supply to the exporter. Specific handling of different exporter
    /// variations is implemented in the corpus file.
    Vec<ExporterExpect> exporterExpect;

    QFileInfo debugFile(QString relativePath, bool create = true) const;
    Dbg       dbg;

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

    ParseSpec(CR<yaml> node, CR<QString> specFile);

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

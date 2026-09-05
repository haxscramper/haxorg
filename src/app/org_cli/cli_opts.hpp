#pragma once

#include <argparse/argparse.hpp>
#include <haxorg/api/ParseContext.hpp>
#include <hstd/stdlib/Opt.hpp>

#define OPT_NAME(__field, __value) static constexpr char const* __field = __value;

#define OPT_FIELD(__field, __value, __type, __default_value)                             \
    OPT_NAME(__field##_opt, __value);                                                    \
    __type __field = __default_value;

#define OPT_GET(__cmd, __opts, __field, __type)                                          \
    if (auto __value = __cmd.present<__type>(__opts.__field##_opt);                      \
        __value.has_value()) {                                                           \
        __opts.__field = __value.value();                                                \
    }

#define OPT_GET_ENUM(__cmd, __opts, __field, __type)                                     \
    if (auto __value = __cmd.present<std::string>(__opts.__field##_opt);                 \
        __value.has_value()) {                                                           \
        __opts.__field = readEnumValue<__type>(__value.value(), "");                     \
    }

namespace org::cli {


struct CliOpts {
    using OS = hstd::Opt<std::string>;

    DECL_DESCRIBED_ENUM(ProtoFormat, Binary, Json, Xml);

    struct DiagramOpts {
        DECL_DESCRIBED_ENUM(InputFormat, Binary, Json);

        OPT_FIELD(input, "input", std::string, "");
        OPT_FIELD(output, "output", std::string, "");
        OPT_FIELD(format, "--format", ProtoFormat, ProtoFormat::Binary);
        OPT_FIELD(input_format, "--input-format", InputFormat, InputFormat::Binary);
        OPT_FIELD(
            serial_read_log,
            "--serial-read-log",
            hstd::Opt<std::string>,
            std::nullopt);
        OPT_FIELD(layout_log, "--layout-log", hstd::Opt<std::string>, std::nullopt);
        OPT_FIELD(output_visual, "--output-visual", hstd::Opt<std::string>, std::nullopt);
        OPT_FIELD(
            output_visual_json,
            "--output-visual-json",
            hstd::Opt<std::string>,
            std::nullopt);
        OPT_FIELD(output_visual_debug, "--output-visual-debug", bool, false);
        DESC_FIELDS(
            DiagramOpts,
            (input,
             output,
             format,
             input_format,
             serial_read_log,
             layout_log,
             output_visual));
    };


    struct ParseOpts {
        /// \brief input file or directory
        OPT_FIELD(input, "input", std::string, "");
        OPT_FIELD(
            lastStage,
            "--last-stage",
            org::parse::OrgParseParameters::LastParseStage,
            org::parse::OrgParseParameters::LastParseStage::ImmConvert);
        OPT_FIELD(validateBaseTokens, "--validate-base-tokens", bool, false);

        OPT_FIELD(baseTokenTracePath, "--base-token-trace", OS, std::nullopt);
        OPT_FIELD(tokenTracePath, "--token-trace", OS, std::nullopt);
        OPT_FIELD(parseTracePath, "--parse-trace", OS, std::nullopt);
        OPT_FIELD(semTracePath, "--sem-trace", OS, std::nullopt);
        OPT_FIELD(baseTokenDumpPath, "--base-token-dump", OS, std::nullopt);
        OPT_FIELD(tokenDumpPath, "--token-dump", OS, std::nullopt);
        OPT_FIELD(parseDumpPath, "--parse-dump", OS, std::nullopt);
        OPT_FIELD(semDumpPath, "--sem-dump", OS, std::nullopt);
        OPT_FIELD(immVerboseDumpPath, "--imm-verbose-dump", OS, std::nullopt);
        OPT_FIELD(immDumpPath, "--imm-dump", OS, std::nullopt);
        OPT_FIELD(immTrackingDumpPath, "--imm-tracking-dump", OS, std::nullopt);
        OPT_FIELD(immAstTracePath, "--imm-convert-trace", OS, std::nullopt);

        ParseOpts() {}
        DESC_FIELDS(
            ParseOpts,
            (input,
             baseTokenTracePath,
             tokenTracePath,
             semTracePath,
             baseTokenDumpPath,
             tokenDumpPath,
             parseDumpPath,
             semDumpPath,
             immVerboseDumpPath,
             immDumpPath,
             immTrackingDumpPath,
             validateBaseTokens,
             immAstTracePath));
    };

    struct ExportOpts {
        struct Json {
            // TODO: Rename the fields to "show empty lists" with default value false.
            bool skipEmptyLists = false;
            bool skipLocation   = false;
            bool skipId         = false;
            bool skipNullFields = false;
            /// \brief Replace multi-character space with a single one on export.
            bool normalizeSpaces = false;

            OPT_NAME(skipEmptyLists_opt, "--skip-empty-lists");
            OPT_NAME(skipLocation_opt, "--skip-location");
            OPT_NAME(skipId_opt, "--skip-id");
            OPT_NAME(skipNullFields_opt, "--skip-null-fields");
            OPT_NAME(normalizeSpaces_opt, "--normalize-spaces");

            Json() {};
            DESC_FIELDS(
                Json,
                (skipEmptyLists, skipLocation, skipId, skipNullFields, normalizeSpaces));
        };

        struct Yaml {
            bool skipNullFields  = false;
            bool skipFalseFields = false;
            bool skipZeroFields  = false;
            bool skipLocation    = false;
            bool skipId          = false;

            OPT_NAME(skipNullFields_opt, "--skip-null-fields");
            OPT_NAME(skipFalseFields_opt, "--skip-false-fields");
            OPT_NAME(skipZeroFields_opt, "--skip-zero-fields");
            OPT_NAME(skipLocation_opt, "--skip-location");
            OPT_NAME(skipId_opt, "--skip-id");

            DESC_FIELDS(
                Yaml,
                (skipNullFields, skipFalseFields, skipZeroFields, skipLocation, skipId));
            Yaml() {}
        };


        struct Token {
            DESC_FIELDS(Token, ());
        };

        struct BaseToken {
            DESC_FIELDS(BaseToken, ());
        };

        struct ParseNode {
            DESC_FIELDS(ParseNode, ());
        };

        struct Proto {
            ProtoFormat format = ProtoFormat::Binary;
            OPT_NAME(format_opt, "--format");
            DESC_FIELDS(Proto, (format));
        };

        struct Map {
            ProtoFormat          format     = ProtoFormat::Binary;
            hstd::Opt<hstd::Str> graphTrace = std::nullopt;

            OPT_NAME(graphTrace_opt, "--graph-trace");
            OPT_NAME(format_opt, "--format");
            DESC_FIELDS(Map, (format, graphTrace));
        };

        SUB_VARIANTS(
            Kind,
            Data,
            data,
            getKind,
            Json,
            Yaml,
            Token,
            BaseToken,
            ParseNode,
            Proto,
            Map);

        Data data;

        std::optional<std::string> exportTrace;
        std::vector<std::string>   input;
        // TODO: Support writing output result to stdout.
        std::string output;

        OPT_NAME(input_opt, "--input");
        OPT_NAME(output_opt, "--output");
        OPT_NAME(exportTrace_opt, "--export-trace");

        ExportOpts() {}
        DESC_FIELDS(ExportOpts, (exportTrace, input, output, data));
    };

    using MainCmd = std::variant<ParseOpts, ExportOpts, DiagramOpts>;
    MainCmd cmd;
    bool    withIncludes = true;
    // FIXME: Add sub-variants to the JSON input parsing.
    DESC_FIELDS(CliOpts, (withIncludes, loggingFlags, logFile, cmd));

    OPT_NAME(withIncludes_opt, "--with-includes");

    DECL_DESCRIBED_ENUM(LoggingFlags, LogToStdout, LogToFile, None);
    hstd::IntSet<LoggingFlags> loggingFlags{LoggingFlags::LogToStdout};

    OPT_NAME(loggingFlags_opt, "--logging-flags");

    OPT_FIELD(logStructured, "--log-structured", bool, false);
    OPT_FIELD(logFile, "--root-log-file", OS, std::nullopt);
    OPT_FIELD(diagnosticsFile, "--diagnostics-file", OS, std::nullopt);
    OPT_FIELD(perfFile, "--perf-file", OS, std::nullopt);
};


[[noreturn]] inline void exitWithError(std::string const& msg) {
    std::cerr << msg << "\n";
    std::exit(1);
}

template <typename E>
std::string lower_enum(E value) {
    std::string result = hstd::fmt1(value);
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return result;
}

template <typename E>
std::string describe_subcommands() {
    return hstd::join(
        ", "_str_view,
        hstd::own_view(hstd::describe_enumerators_as_array<E>())
            | hstd::rv::transform([](E k) -> std::string { return lower_enum(k); }));
}


template <typename E>
std::string describe_enum() {
    return hstd::join(
        ", "_str_view,
        hstd::own_view(hstd::describe_enumerators_as_array<E>())
            | hstd::rv::transform([](E k) -> std::string { return hstd::fmt1(k); }));
}

template <typename E>
E readEnumValue(std::string const& value, std::string const& message) {
    auto parsed = hstd::from_string_insensitive<E>(value);
    if (parsed.has_value()) {
        return parsed.value();
    } else {
        exitWithError(
            hstd::fmt(
                "unexpected value: {} expected: {} for {}",
                value,
                describe_enum<E>(),
                message));
    }
}

/// \brief Add a boolean option that takes an explicit `true`/`false` value and
/// defaults to \p def when not provided on the command line.
void addBoolOpt(
    argparse::ArgumentParser& p,
    char const*               name,
    char const*               help,
    bool                      def);

CliOpts parseCli(int argc, char** argv);

} // namespace org::cli

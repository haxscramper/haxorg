#include "haxorg/exporters/ExporterJson.hpp"
#include "haxorg/exporters/exporteryaml.hpp"
#include "proto_to_xml.hpp"
#include "src/haxorg/imm/ImmOrgGraph.pb.h"
#include "src/haxorg/serde/OrgApiProto.pb.h"
#include "src/haxorg/serde/SemOrgProto.pb.h"
#include <argparse/argparse.hpp>
#include <boost/describe.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/mp11.hpp>
#include <fmt/base.h>
#include <fmt/format.h>
#include <fstream>
#include <google/protobuf/util/json_util.h>
#include <haxorg/api/ParseContext.hpp>
#include <haxorg/imm/ImmGetterApi.hpp>
#include <haxorg/imm/ImmOrg.hpp>
#include <haxorg/imm/ImmOrgEdit.hpp>
#include <haxorg/imm/ImmOrgGraph.hpp>
#include <haxorg/lexbase/NodeIO.hpp>
#include <haxorg/test/NodeTest.hpp>
#include <hstd/ext/error_write_proto.hpp>
#include <hstd/ext/logger.hpp>
#include <hstd/stdlib/IntSetSerde.hpp>
#include <hstd/stdlib/JsonCLIParser.hpp>
#include <hstd/stdlib/OptFormatter.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/VariantFormatter.hpp>
#include <hstd/stdlib/VariantSerde.hpp>
#include <optional>
#include <string>
#include <vector>

#include <haxorg/sem/perfetto_org.hpp>
#include <hstd/ext/perfetto_aux_impl_template.hpp>

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

hstd::ProtoXmlMapper make_proto_xml_mapper();

struct ParseReports {
    std::string       formatted;
    hstd::ext::Report report;
};

template <>
struct hstd::serde::proto_serde<orgproto::ParseReport, ParseReports> {
    static void write(orgproto::ParseReport* out, ParseReports const& in) {
        out->set_formatted(in.formatted);
        hstd::serde::write_serde(out->mutable_report(), in.report);
    }

    static void read(orgproto::ParseReport const& in, ParseReports* out) {
        out->formatted = in.formatted();
        hstd::serde::read_serde(in.report(), &out->report);
    }
};

struct CliOpts {
    using OS = hstd::Opt<std::string>;
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
             validateBaseTokens));
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

#if ORG_BUILD_WITH_PROTOBUF
        DECL_DESCRIBED_ENUM(ProtoFormat, Binary, Json, Xml);

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
            DESC_FIELDS(Map, (format));
        };
#endif


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

    using MainCmd = std::variant<ParseOpts, ExportOpts>;
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


namespace {

[[noreturn]] void exitWithError(std::string const& msg) {
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
    bool                      def) {
    p.add_argument(name).help(help).default_value(def).action(
        [](std::string const& v) -> bool { return v == "true" || v == "1"; });
}

CliOpts::ExportOpts buildExportOpts(argparse::ArgumentParser& export_cmd) {
    using EO = CliOpts::ExportOpts;
    using EK = EO::Kind;

    CliOpts::ExportOpts opts;
    opts.input  = export_cmd.get<std::vector<std::string>>(EO::input_opt);
    opts.output = export_cmd.get<std::string>(EO::output_opt);

    if (auto v = export_cmd.present<std::string>(EO::exportTrace_opt)) {
        opts.exportTrace = *v;
    }

    if (export_cmd.is_subcommand_used(lower_enum(EK::Json))) {
        auto&    sub = export_cmd.at<argparse::ArgumentParser>(lower_enum(EK::Json));
        EO::Json json;
        OPT_GET(sub, json, skipEmptyLists, bool);
        OPT_GET(sub, json, skipLocation, bool);
        OPT_GET(sub, json, skipId, bool);
        OPT_GET(sub, json, skipNullFields, bool);
        OPT_GET(sub, json, normalizeSpaces, bool);
        opts.data = json;
    } else if (export_cmd.is_subcommand_used(lower_enum(EK::Yaml))) {
        auto&    sub = export_cmd.at<argparse::ArgumentParser>(lower_enum(EK::Yaml));
        EO::Yaml yaml;
        OPT_GET(sub, yaml, skipNullFields, bool);
        OPT_GET(sub, yaml, skipFalseFields, bool);
        OPT_GET(sub, yaml, skipZeroFields, bool);
        OPT_GET(sub, yaml, skipLocation, bool);
        OPT_GET(sub, yaml, skipId, bool);
        opts.data = yaml;
#if ORG_BUILD_WITH_PROTOBUF
    } else if (export_cmd.is_subcommand_used(lower_enum(EK::Proto))) {
        auto&     sub = export_cmd.at<argparse::ArgumentParser>(lower_enum(EK::Proto));
        EO::Proto res;
        OPT_GET_ENUM(sub, res, format, EO::ProtoFormat);
        opts.data = res;
    } else if (export_cmd.is_subcommand_used(lower_enum(EK::Map))) {
        auto&   sub = export_cmd.at<argparse::ArgumentParser>(lower_enum(EK::Map));
        EO::Map res;
        OPT_GET_ENUM(sub, res, format, EO::ProtoFormat);
        opts.data = res;
#endif
    } else if (export_cmd.is_subcommand_used(lower_enum(EK::Token))) {
        opts.data = EO::Token{};
    } else if (export_cmd.is_subcommand_used(lower_enum(EK::BaseToken))) {
        opts.data = EO::BaseToken{};
    } else if (export_cmd.is_subcommand_used(lower_enum(EK::ParseNode))) {
        opts.data = EO::ParseNode{};
    } else {
        exitWithError(
            "export: missing export type subcommand, expected: "
            + describe_subcommands<EK>());
    }

    return opts;
}

} // namespace

static std::vector<std::string> expandAtFiles(int argc, char** argv) {
    std::vector<std::string> args;
    args.reserve(argc);
    for (int i = 0; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.size() > 1 && arg[0] == '@') {
            std::ifstream in{arg.substr(1)};
            if (!in) {
                throw std::runtime_error{"cannot open response file: " + arg.substr(1)};
            }
            std::string tok;
            while (in >> tok) { args.push_back(std::move(tok)); }
        } else {
            args.push_back(std::move(arg));
        }
    }
    return args;
}


CliOpts parseCli(int argc, char** argv) {
    using EO = CliOpts::ExportOpts;
    using EK = EO::Kind;
    using PO = CliOpts::ParseOpts;

    argparse::ArgumentParser program("haxorg");
    program.add_epilog(
        hstd::fmt("ORG_BUILD_WITH_PROTOBUF = {}", ORG_BUILD_WITH_PROTOBUF));

    addBoolOpt(program, CliOpts::withIncludes_opt, "parse input with all includes", true);
    program.add_argument(CliOpts::loggingFlags_opt)
        .help("set logging flag values")
        .append();
    program.add_argument(CliOpts::logFile_opt)
        .help(
            "main log file for the CLI. It will contain all the internal messages "
            "(debug, tracing -- everything that the end user most likely not interested "
            "in)");
    program.add_argument(CliOpts::diagnosticsFile_opt)
        .help(
            "Optional file to write parse diagnostics (errors, warnings -- all sorts of "
            "user-facing messages) to.");
    program.add_argument(CliOpts::perfFile_opt)
        .help(
            "Optional file to write perfetto profiling diagnostics to (the code must be "
            "compiled with perfetto enabled)");

    argparse::ArgumentParser parse_cmd("parse");
    parse_cmd.add_description("parse input file or directory");
    parse_cmd.add_argument(PO::input_opt).help("input file or directory");
    parse_cmd.add_argument(PO::baseTokenTracePath_opt)
        .help("base token trace output path");
    parse_cmd.add_argument(PO::tokenTracePath_opt).help("token trace output path");
    parse_cmd.add_argument(PO::parseTracePath_opt).help("parse trace output path");
    parse_cmd.add_argument(PO::semTracePath_opt).help("sem trace output path");
    parse_cmd.add_argument(PO::baseTokenDumpPath_opt).help("base token dump output path");
    parse_cmd.add_argument(PO::tokenDumpPath_opt).help("token dump output path");
    parse_cmd.add_argument(PO::parseDumpPath_opt).help("parse dump output path");
    parse_cmd.add_argument(PO::semDumpPath_opt).help("sem dump output path");
    parse_cmd.add_argument(PO::immDumpPath_opt).help("Non-verbose dump of immutable AST");
    parse_cmd.add_argument(PO::immAstTracePath_opt).help("Trace imm ast construct");
    parse_cmd.add_argument(PO::immVerboseDumpPath_opt)
        .help("Verbose dump of immutable AST");
    parse_cmd.add_argument(PO::immTrackingDumpPath_opt)
        .help("Dump of immutable AST tracking information");
    parse_cmd.add_argument(PO::validateBaseTokens_opt)
        .help(
            "Whether to check the base tokens for consistency. This is a dev/debug "
            "option");
    parse_cmd.add_argument(PO::lastStage_opt)
        .help(
            "Stop parsing at the specified stage, this is a primarily for "
            "debugging/profiling individual stages, unless the last stage is set to "
            "SemConvert, the parser will not try to collect any diagnostics or return "
            "any values. Allowed values "
            + describe_enum<org::parse::OrgParseParameters::LastParseStage>());

    program.add_subparser(parse_cmd);

    argparse::ArgumentParser export_cmd("export");
    export_cmd.add_description(
        "export parsed document; pick a target: " + describe_subcommands<EK>());
    export_cmd.add_argument(EO::input_opt)
        .help("input org file (repeatable)")
        .required()
        .append();
    export_cmd.add_argument(EO::output_opt).help("output file").required();
    export_cmd.add_argument(EO::exportTrace_opt).help("export trace path");

    argparse::ArgumentParser json_cmd(lower_enum(EK::Json));
    json_cmd.add_description("export to json");
    addBoolOpt(
        json_cmd, EO::Json::skipEmptyLists_opt, "skip empty lists on export", true);
    addBoolOpt(json_cmd, EO::Json::skipLocation_opt, "skip location fields", true);
    addBoolOpt(json_cmd, EO::Json::skipId_opt, "skip id fields", true);
    addBoolOpt(json_cmd, EO::Json::skipNullFields_opt, "skip null fields", true);
    addBoolOpt(
        json_cmd,
        EO::Json::normalizeSpaces_opt,
        "replace multi-character space with a single one",
        true);
    export_cmd.add_subparser(json_cmd);

    argparse::ArgumentParser yaml_cmd(lower_enum(EK::Yaml));
    yaml_cmd.add_description("export to yaml");
    addBoolOpt(yaml_cmd, EO::Yaml::skipNullFields_opt, "skip null fields", true);
    addBoolOpt(yaml_cmd, EO::Yaml::skipFalseFields_opt, "skip false fields", true);
    addBoolOpt(yaml_cmd, EO::Yaml::skipZeroFields_opt, "skip zero fields", true);
    addBoolOpt(yaml_cmd, EO::Yaml::skipLocation_opt, "skip location fields", true);
    addBoolOpt(yaml_cmd, EO::Yaml::skipId_opt, "skip id fields", true);
    export_cmd.add_subparser(yaml_cmd);

    argparse::ArgumentParser token_cmd(lower_enum(EK::Token));
    token_cmd.add_description("export tokenizer result");
    export_cmd.add_subparser(token_cmd);

    argparse::ArgumentParser basetoken_cmd(lower_enum(EK::BaseToken));
    basetoken_cmd.add_description("export base tokenizer result");
    export_cmd.add_subparser(basetoken_cmd);

    argparse::ArgumentParser parsenode_cmd(lower_enum(EK::ParseNode));
    parsenode_cmd.add_description("export parse node result");
    export_cmd.add_subparser(parsenode_cmd);

#if ORG_BUILD_WITH_PROTOBUF
    argparse::ArgumentParser proto_cmd(lower_enum(EK::Proto));
    proto_cmd.add_description("export to protobuf");
    proto_cmd.add_argument(EO::Proto::format_opt)
        .help("set protobuf export format: " + describe_enum<EO::ProtoFormat>());
    export_cmd.add_subparser(proto_cmd);

    argparse::ArgumentParser map_cmd(lower_enum(EK::Map));
    map_cmd.add_description("export to map");
    map_cmd.add_argument(EO::Map::format_opt)
        .help("set map export format: " + describe_enum<EO::ProtoFormat>());
    map_cmd.add_argument(EO::Map::graphTrace_opt).help("graph trace output path");
    export_cmd.add_subparser(map_cmd);
#endif

    program.add_subparser(export_cmd);


    auto expanded = expandAtFiles(argc, argv);
    try {
        std::vector<char*> expandedPtrs;
        expandedPtrs.reserve(expanded.size());
        for (auto& s : expanded) { expandedPtrs.push_back(s.data()); }

        program.parse_args(expandedPtrs.size(), expandedPtrs.data());
    } catch (std::exception const& e) {
        std::cerr << hstd::fmt(
            R"({}
{}
Full argument list was:
{})",
            e.what(),
            program.help().str(),
            expanded);

        std::exit(1);
    }

    CliOpts result;
    result.withIncludes = program.get<bool>(CliOpts::withIncludes_opt);

    if (auto flags = program.present<std::vector<std::string>>(
            CliOpts::loggingFlags_opt)) {
        result.loggingFlags = hstd::IntSet<CliOpts::LoggingFlags>{};
        for (auto const& value : *flags) {
            result.loggingFlags.incl(
                readEnumValue<CliOpts::LoggingFlags>(value, "logging flag"));
        }
    }

    if (auto f = program.present<std::string>(CliOpts::logFile_opt)) {
        result.logFile = *f;
    }

    if (auto f = program.present<std::string>(CliOpts::diagnosticsFile_opt)) {
        result.diagnosticsFile = *f;
    }

    if (auto f = program.present<std::string>(CliOpts::perfFile_opt)) {
        result.perfFile = *f;
    }

    if (program.is_subcommand_used("parse")) {
        CliOpts::ParseOpts opts;
        opts.input = parse_cmd.get<std::string>(PO::input_opt);
        OPT_GET(parse_cmd, opts, baseTokenTracePath, std::string);
        OPT_GET(parse_cmd, opts, tokenTracePath, std::string);
        OPT_GET(parse_cmd, opts, parseTracePath, std::string);
        OPT_GET(parse_cmd, opts, semTracePath, std::string);
        OPT_GET(parse_cmd, opts, baseTokenDumpPath, std::string);
        OPT_GET(parse_cmd, opts, tokenDumpPath, std::string);
        OPT_GET(parse_cmd, opts, parseDumpPath, std::string);
        OPT_GET(parse_cmd, opts, semDumpPath, std::string);
        OPT_GET(parse_cmd, opts, immDumpPath, std::string);
        OPT_GET(parse_cmd, opts, immVerboseDumpPath, std::string);
        OPT_GET(parse_cmd, opts, immAstTracePath, std::string);
        OPT_GET(parse_cmd, opts, immTrackingDumpPath, std::string);
        if (auto v = parse_cmd.present<std::string>(opts.validateBaseTokens_opt)) {
            // TODO: boost lexical cast fails here, but writing a template function that
            // extracts the user-provided varibles in a sensible manner (e.g. interpreting
            // "true" string as `true` value, which is pretty fucking obvious IMO).
            opts.validateBaseTokens = v.value() == "true";
        }
        OPT_GET_ENUM(
            parse_cmd, opts, lastStage, org::parse::OrgParseParameters::LastParseStage);
        result.cmd = opts;
    } else if (program.is_subcommand_used("export")) {
        result.cmd = buildExportOpts(export_cmd);
    } else {
        std::cerr << "missing command (expected 'parse' or 'export')\n" << program;
        std::exit(1);
    }

    return result;
}

int main(int argc, char* argv[]) {
    // TODO: Support `@input-file` syntax for passing multiple options to the CLI from a
    // file.
    auto opts //
        = argc == 2 && std::string{argv[1]}.starts_with("/")
            ? hstd::parse_json_argc<CliOpts>(argc, argv)
            : parseCli(argc, argv);

    hstd::log::clear_sink_backends();
    if (opts.loggingFlags.contains(CliOpts::LoggingFlags::LogToFile)) {
        LOGIC_ASSERTION_CHECK(opts.logFile.has_value(), "Expected value for log file");
        hstd::log::push_sink(
            hstd::log::init_file_sink(opts.logFile.value(), opts.logStructured));
    }

    if (opts.loggingFlags.contains(CliOpts::LoggingFlags::LogToStdout)) {
        hstd::log::push_sink(hstd::log::init_stdout_sink(opts.logStructured));
    }

    HSLOG_INFO("starting");
    HSLOG_TRACE("CLI opts: {}", opts);

    auto pathCB = [](std::string const& path) -> bool {
        // TODO: make this configurable
        hstd::fs::path p{path};
        if (path.contains(".git") || path.contains(".trunk")) {
            return false;
        } else if (path.ends_with(".org")) {
            return true;
        } else {
            return hstd::fs::is_directory(p);
        }
    };

    auto ctx = std::make_shared<org::parse::ParseContext>();

    std::ofstream fileOut;
    std::ostream* diagOut = &std::cerr;
    if (opts.diagnosticsFile) {
        auto const& path = hstd::fs::path{opts.diagnosticsFile.value()};
        std::filesystem::create_directories(path.parent_path());
        fileOut.open(path, std::ios::out | std::ios::trunc);
        if (!fileOut.is_open()) {
            throw std::runtime_error(
                hstd::fmt("failed to open diagnostics file {}", path));
        }
        HSLOG_INFO("using diag file {}", path);
        diagOut = &fileOut;
    }

    *diagOut << "" << std::endl;

#ifdef ORG_BUILD_WITH_PERFETTO

    std::unique_ptr<perfetto::TracingSession>
        tracing_session = opts.perfFile ? StartProcessTracing("Perfetto track example")
                                        : std::unique_ptr<perfetto::TracingSession>{};

    hstd::finally end_trace{[&]() {
        if (opts.perfFile) {
            StopTracing(std::move(tracing_session), opts.perfFile.value());
        }
    }};
#endif

    if (std::holds_alternative<CliOpts::ParseOpts>(opts.cmd)) {
        auto const&    cmd = std::get<CliOpts::ParseOpts>(opts.cmd);
        hstd::fs::path input{cmd.input};

        auto params                    = org::parse::OrgParseParameters::shared();
        params->parseTracePath         = cmd.parseTracePath;
        params->baseTokenTracePath     = cmd.baseTokenTracePath;
        params->tokenTracePath         = cmd.tokenTracePath;
        params->semTracePath           = cmd.semTracePath;
        params->onDiagnosticsCollected = [&](hstd::Vec<hstd::ext::Report> const& reports,
                                             std::optional<int> fragmentIndex) {
            auto cache = ctx->getDiagnosticStrings();
            for (auto const& report : reports) {
                auto tmp = report;
                *diagOut << tmp.to_string(*cache, false) << std::endl;
            }
        };
        params->lastStage          = cmd.lastStage;
        params->validateBaseTokens = cmd.validateBaseTokens;

        params->onParseDone = [&](org::parse::OrgNodeGroup const& nodes,
                                  org::parse::OrgId               id,
                                  std::optional<int>              fragmentIndex) {
            if (cmd.parseDumpPath) {
                hstd::writeFile(cmd.parseDumpPath.value(), nodes.treeRepr(id), true);
            }
        };

        auto directoryParsingOpts = org::parse::OrgDirectoryParseParameters::shared();


        directoryParsingOpts->shouldProcessPath = pathCB;

        directoryParsingOpts->getParsedNode =
            [&](std::string const& path) -> org::sem::SemId<org::sem::Org> {
            return ctx->parseFileOpts(path, params);
        };

        org::sem::SemId<org::sem::Org> node;

        if (hstd::fs::is_directory(input)) {
            node = ctx->parseDirectoryOpts(input, directoryParsingOpts).value();
        } else {
            if (opts.withIncludes) {
                node = ctx->parseFileWithIncludes(input, directoryParsingOpts);
            } else {
                node = ctx->parseFileOpts(input, params);
            }
        }

        if (cmd.lastStage == org::parse::OrgParseParameters::LastParseStage::ImmConvert) {
            auto store = org::imm::ImmAstContext::init_start_context();
            if (cmd.immAstTracePath) {
                store->debug->setTraceFile(cmd.immAstTracePath.value());
            }
            auto version  = store->init(node);
            auto imm_node = version.getRootAdapter();

            if (cmd.immDumpPath) {
                hstd::writeFile(
                    cmd.immDumpPath.value(),
                    imm_node.treeRepr(org::imm::ImmAdapter::TreeReprConf{})
                        .toString(false),
                    true);
            }

            if (cmd.immVerboseDumpPath) {
                hstd::writeFile(
                    cmd.immVerboseDumpPath.value(),
                    imm_node
                        .treeRepr(
                            org::imm::ImmAdapter::TreeReprConf{
                                .withAuxFields  = true,
                                .withReflFields = true,
                            })
                        .toString(false),
                    true);
            }

            if (cmd.immTrackingDumpPath) {
                hstd::writeFile(
                    cmd.immTrackingDumpPath.value(),
                    version.getContext()->currentTrack->toString().toString(false),
                    true);
            }
        }
    } else {
        using EO        = CliOpts::ExportOpts;
        auto const& cmd = std::get<EO>(opts.cmd);


        auto directoryParsingOpts = org::parse::OrgDirectoryParseParameters::shared();

        directoryParsingOpts->shouldProcessPath = pathCB;

        json parse_lefovers_export{};

        hstd::Vec<ParseReports> reports;

        auto paramsForPath = [&](std::string const& path) {
            auto params                    = org::parse::OrgParseParameters::shared();
            params->onDiagnosticsCollected = [&](hstd::Vec<hstd::ext::Report> const& tmp,
                                                 std::optional<int> fragmentIndex) {
                auto cache = ctx->getDiagnosticStrings();
                for (auto const& rep : tmp) {
                    reports.push_back(
                        ParseReports{
                            .formatted = rep.to_string(*cache, false),
                            .report    = rep,
                        });
                }
            };

            auto group_json_repr = [&](auto const&        group,
                                       std::optional<int> fragmentIndex) -> json {
                return json::object({
                    {"path", path},
                    {"group", org::test::jsonRepr(group)},
                    {"fragment_index",
                     fragmentIndex.has_value() ? json{fragmentIndex.value()} : json{}},
                });
            };

            std::visit(
                hstd::overloaded{
                    [&](EO::Token const& j) -> void {
                        params->onTokenizerDone =
                            [&](org::parse::OrgTokenGroup const& tokens,
                                std::optional<int>               fragmentIndex) {
                                parse_lefovers_export["tokenizer_export"].push_back(
                                    group_json_repr(tokens, fragmentIndex));
                            };
                    },
                    [&](EO::BaseToken const& j) -> void {
                        params->onBaseTokenizeDone =
                            [&](org::parse::OrgTokenGroup const& tokens,
                                std::optional<int>               fragmentIndex) {
                                parse_lefovers_export["base_tokenizer_export"].push_back(
                                    group_json_repr(tokens, fragmentIndex));
                            };
                    },
                    [&](EO::ParseNode const& j) -> void {
                        params->onParseDone = [&](org::parse::OrgNodeGroup const& tokens,
                                                  org::parse::OrgId               id,
                                                  std::optional<int> fragmentIndex) {
                            parse_lefovers_export["parse_export"].push_back(
                                group_json_repr(tokens, fragmentIndex));
                        };
                    },
                    [&](auto const& j) -> void {},
                },
                cmd.data);

            return params;
        };

        auto pathToNode = [&](std::string const& path) -> org::sem::SemId<org::sem::Org> {
            return ctx->parseFileOpts(path, paramsForPath(path));
        };

        directoryParsingOpts->getParsedNode = pathToNode;

        // TODO: Support multiple inputs and unify all parsed nodes into a single group.
        hstd::fs::path input{cmd.input.at(0)};

        auto node = hstd::fs::is_directory(input)
                      ? ctx->parseDirectoryOpts(input, directoryParsingOpts)
                      : (opts.withIncludes
                             ? ctx->parseFileWithIncludes(input, directoryParsingOpts)
                             : ctx->parseFileOpts(input, paramsForPath(input)));

        auto write_proto_json = [&](google::protobuf::Message const& result) {
            std::string                          json;
            google::protobuf::json::PrintOptions j_opts;
            j_opts.add_whitespace = true;
            auto status           = google::protobuf::util::MessageToJsonString(
                result, &json, j_opts);

            hstd::writeFile(cmd.output, json, true);
        };


        auto write_proto_binary = [&](google::protobuf::Message const& result) {
            std::ofstream out(cmd.output, std::ios::binary);
            result.SerializeToOstream(&out);
        };

        auto write_proto_xml = [&](google::protobuf::Message const& result) {
            auto          mapper = make_proto_xml_mapper();
            std::ofstream out(cmd.output);
            mapper.map(result).serialize(out);
        };

        auto write_proto_result = [&](google::protobuf::Message const& result,
                                      EO::ProtoFormat const&           format) {
            switch (format) {
                case EO::ProtoFormat::Json: write_proto_json(result); break;
                case EO::ProtoFormat::Binary: write_proto_binary(result); break;
                case EO::ProtoFormat::Xml: write_proto_xml(result); break;
            }
        };

        std::visit(
            hstd::overloaded{
                [&](EO::Json const& j) -> void {
                    org::algo::ExporterJson exp;
                    exp.skipEmptyLists  = j.skipEmptyLists;
                    exp.skipId          = j.skipId;
                    exp.skipLocation    = j.skipLocation;
                    exp.skipNullFields  = j.skipNullFields;
                    exp.normalizeSpaces = j.normalizeSpaces;
                    auto res            = exp.evalTop(node.value());
                    hstd::writeFile(cmd.output, res.dump(2), true);
                },
                [&](EO::Yaml const& j) -> void {
                    org::algo::ExporterYaml exp;
                    exp.skipNullFields  = j.skipNullFields;
                    exp.skipFalseFields = j.skipFalseFields;
                    exp.skipZeroFields  = j.skipZeroFields;
                    exp.skipLocation    = j.skipLocation;
                    exp.skipId          = j.skipId;
                    auto res            = exp.evalTop(node.value());
                    hstd::writeFile(cmd.output, fmt::format("{}\n", res), true);
                },
                [&](EO::Token const& j) -> void {
                    hstd::writeFile(cmd.output, parse_lefovers_export.dump(2), true);
                },
                [&](EO::BaseToken const& j) -> void {
                    hstd::writeFile(cmd.output, parse_lefovers_export.dump(2), true);
                },
                [&](EO::ParseNode const& j) -> void {
                    hstd::writeFile(cmd.output, parse_lefovers_export.dump(2), true);
                },
#if ORG_BUILD_WITH_PROTOBUF
                [&](EO::Proto const& p) {
                    HSLOG_INFO("Converting parse result to protobuf");
                    orgproto::ParseResult result;
                    hstd::serde::write_serde(result.mutable_node(), node.value());
                    hstd::serde::write_serde(result.mutable_sources(), *ctx->source);
                    hstd::serde::write_serde(result.mutable_reports(), reports);
                    HSLOG_INFO("Serializing protobuf result to output file");
                    write_proto_result(result, p.format);
                },
                [&](EO::Map const& m) {
                    org::graph::MapConfig::Ptr   conf{org::graph::MapConfig::shared()};
                    org::imm::ImmAstContext::Ptr store{
                        org::imm::ImmAstContext::init_start_context()};
                    HSLOG_INFO("Converting to immutable AST");
                    org::imm::ImmAstVersion version = store->addRoot(node.value());
                    org::graph::MapGraphState::Ptr
                         state   = org::graph::MapGraphState::shared(version.context);
                    auto adapter = version.getRootAdapter();
                    HSLOG_INFO("Building immutable AST graph");
                    state->addNodeRec(adapter.ctx.lock(), adapter, conf);

                    HSLOG_INFO("Writing graph to protobuf data");
                    org::graph::proto::GraphResult result;
                    result.set_allocated_graph(state->graph->get_serial().release());
                    hstd::serde::write_serde(result.mutable_sources(), *ctx->source);
                    hstd::serde::write_serde(result.mutable_reports(), reports);

                    HSLOG_INFO("Serializing protobuf result to output file");
                    write_proto_result(result, m.format);
                },
#endif
            },
            cmd.data);
    }

    HSLOG_INFO("Done file processing");
}

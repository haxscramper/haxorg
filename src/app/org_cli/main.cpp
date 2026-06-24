#include "haxorg/exporters/ExporterJson.hpp"
#include "haxorg/exporters/exporteryaml.hpp"
#include "haxorg/serde/SemOrgSerde.hpp"
#include "src/haxorg/serde/SemOrgProto.pb.h"
#include <argparse/argparse.hpp>
#include <boost/describe.hpp>
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

#define OPT_NAME(__field, __value) static constexpr char const* __field = __value;

struct CliOpts {
    struct ParseOpts {
        /// \brief input file or directory
        std::string            input;
        hstd::Opt<std::string> baseTokenTracePath = std::nullopt;
        hstd::Opt<std::string> tokenTracePath     = std::nullopt;
        hstd::Opt<std::string> parseTracePath     = std::nullopt;
        hstd::Opt<std::string> semTracePath       = std::nullopt;

        OPT_NAME(input_opt, "input");
        OPT_NAME(baseTokenTracePath_opt, "--base-token-trace");
        OPT_NAME(tokenTracePath_opt, "--token-trace");
        OPT_NAME(parseTracePath_opt, "--parse-trace");
        OPT_NAME(semTracePath_opt, "--sem-trace");

        ParseOpts() {}
        DESC_FIELDS(ParseOpts, (input, baseTokenTracePath, tokenTracePath, semTracePath));
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
            DECL_DESCRIBED_ENUM(ProtoFormat, Binary, Json);
            ProtoFormat format = ProtoFormat::Binary;
            OPT_NAME(format_opt, "--format");
            DESC_FIELDS(Proto, (format));
        };

        struct Map {
            DECL_DESCRIBED_ENUM(MapFormat, Binary, Json);
            MapFormat            format     = MapFormat::Binary;
            hstd::Opt<hstd::Str> graphTrace = std::nullopt;

            OPT_NAME(graphTrace_opt, "--graph-trace");
            OPT_NAME(format_opt, "--format");
            DESC_FIELDS(Map, (format));
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

        OPT_NAME(type_opt, "type");
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
    hstd::IntSet<LoggingFlags> loggingFlags{
        LoggingFlags::LogToStdout,
        LoggingFlags::LogToFile,
    };

    OPT_NAME(loggingFlags_opt, "--logging-flags");
    hstd::Opt<hstd::Str> logFile;
    OPT_NAME(logFile_opt, "--root-log-file");
};


namespace {

[[noreturn]] void exitWithError(std::string const& msg) {
    std::cerr << msg << "\n";
    std::exit(1);
}

template <typename E>
std::string describe_enum() {
    return hstd::join(
        ", ",
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

CliOpts::ExportOpts buildExportOpts(argparse::ArgumentParser const& export_cmd) {
    using EO = CliOpts::ExportOpts;
    using EK = EO::Kind;

    CliOpts::ExportOpts opts;
    opts.input  = export_cmd.get<std::vector<std::string>>(EO::input_opt);
    opts.output = export_cmd.get<std::string>(EO::output_opt);

    if (auto v = export_cmd.present<std::string>(EO::exportTrace_opt)) {
        opts.exportTrace = *v;
    }

    std::string const& typeStr = export_cmd.get<std::string>(EO::type_opt);
    auto               kind    = hstd::from_string_insensitive<EK>(typeStr);
    if (!kind.has_value()) {
        exitWithError(
            "export: unknown export type '" + typeStr
            + "' expected: " + describe_enum<EK>());
    }

    switch (kind.value()) {
        case EK::Json: {
            EO::Json json;
            json.skipEmptyLists  = export_cmd.get<bool>(EO::Json::skipEmptyLists_opt);
            json.skipLocation    = export_cmd.get<bool>(EO::Json::skipLocation_opt);
            json.skipId          = export_cmd.get<bool>(EO::Json::skipId_opt);
            json.skipNullFields  = export_cmd.get<bool>(EO::Json::skipNullFields_opt);
            json.normalizeSpaces = export_cmd.get<bool>(EO::Json::normalizeSpaces_opt);
            opts.data            = json;
            break;
        }
        case EK::Yaml: {
            EO::Yaml yaml;
            yaml.skipNullFields  = export_cmd.get<bool>(EO::Yaml::skipNullFields_opt);
            yaml.skipFalseFields = export_cmd.get<bool>(EO::Yaml::skipFalseFields_opt);
            yaml.skipZeroFields  = export_cmd.get<bool>(EO::Yaml::skipZeroFields_opt);
            yaml.skipLocation    = export_cmd.get<bool>(EO::Yaml::skipLocation_opt);
            yaml.skipId          = export_cmd.get<bool>(EO::Yaml::skipId_opt);
            opts.data            = yaml;
            break;
        }
        case EK::Proto: {
            EO::Proto res;
            if (auto v = export_cmd.present<std::string>(EO::Proto::format_opt)) {
                res.format = readEnumValue<EO::Proto::ProtoFormat>(*v, "proto format");
            }
            opts.data = res;
            break;
        }
        case EK::Map: {
            EO::Map res;
            if (auto v = export_cmd.present<std::string>(EO::Map::format_opt)) {
                res.format = readEnumValue<EO::Map::MapFormat>(*v, "map format");
            }
            opts.data = res;
            break;
        }
        case EK::Token: {
            opts.data = EO::Token{};
            break;
        }
        case EK::BaseToken: {
            opts.data = EO::BaseToken{};
            break;
        }
        case EK::ParseNode: {
            opts.data = EO::ParseNode{};
            break;
        }
    }

    return opts;
}

} // namespace

CliOpts parseCli(int argc, char** argv) {
    using EO = CliOpts::ExportOpts;
    using EK = EO::Kind;
    using PO = CliOpts::ParseOpts;

    argparse::ArgumentParser program("haxorg");

    addBoolOpt(program, CliOpts::withIncludes_opt, "parse input with all includes", true);
    program.add_argument(CliOpts::loggingFlags_opt)
        .help("set logging flag values")
        .append();
    program.add_argument(CliOpts::logFile_opt).help("main log file for the CLI");

    argparse::ArgumentParser parse_cmd("parse");
    parse_cmd.add_description("parse input file or directory");
    parse_cmd.add_argument(PO::input_opt).help("input file or directory");
    parse_cmd.add_argument(PO::baseTokenTracePath_opt)
        .help("base token trace output path");
    parse_cmd.add_argument(PO::tokenTracePath_opt).help("token trace output path");
    parse_cmd.add_argument(PO::parseTracePath_opt).help("parse trace output path");
    parse_cmd.add_argument(PO::semTracePath_opt).help("sem trace output path");
    program.add_subparser(parse_cmd);

    argparse::ArgumentParser export_cmd("export");
    export_cmd.add_description("export parsed document");
    export_cmd.add_argument(EO::type_opt).help("export type: " + describe_enum<EK>());
    export_cmd.add_argument(EO::input_opt)
        .help("input org file (repeatable)")
        .required()
        .append();
    export_cmd.add_argument(EO::output_opt).help("output file").required();
    export_cmd.add_argument(EO::exportTrace_opt).help("export trace path");

    // json options
    addBoolOpt(
        export_cmd, EO::Json::skipEmptyLists_opt, "skip empty lists on export", true);
    addBoolOpt(export_cmd, EO::Json::skipLocation_opt, "skip location fields", true);
    addBoolOpt(export_cmd, EO::Json::skipId_opt, "skip id fields", true);
    addBoolOpt(export_cmd, EO::Json::skipNullFields_opt, "skip null fields", true);
    addBoolOpt(
        export_cmd,
        EO::Json::normalizeSpaces_opt,
        "replace multi-character space with a single one",
        true);
    // yaml options
    addBoolOpt(export_cmd, EO::Yaml::skipFalseFields_opt, "skip false fields", true);
    addBoolOpt(export_cmd, EO::Yaml::skipZeroFields_opt, "skip zero fields", true);
    // proto options
    export_cmd.add_argument(EO::Proto::format_opt)
        .help("set protobuf export format: " + describe_enum<EO::Proto::ProtoFormat>());
    // map options
    export_cmd.add_argument(EO::Map::format_opt)
        .help("set map export format: " + describe_enum<EO::Map::MapFormat>());

    program.add_subparser(export_cmd);

    try {
        program.parse_args(argc, argv);
    } catch (std::exception const& e) {
        std::cerr << e.what() << "\n" << program;
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

    if (program.is_subcommand_used("parse")) {
        CliOpts::ParseOpts opts;
        opts.input = parse_cmd.get<std::string>(PO::input_opt);
        if (auto v = parse_cmd.present<std::string>(PO::baseTokenTracePath_opt)) {
            opts.baseTokenTracePath = *v;
        }
        if (auto v = parse_cmd.present<std::string>(PO::tokenTracePath_opt)) {
            opts.tokenTracePath = *v;
        }
        if (auto v = parse_cmd.present<std::string>(PO::parseTracePath_opt)) {
            opts.parseTracePath = *v;
        }
        if (auto v = parse_cmd.present<std::string>(PO::semTracePath_opt)) {
            opts.semTracePath = *v;
        }
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
        // TODO: Get XDG-aware logging file location
        hstd::log::push_sink(
            hstd::log::init_file_sink(opts.logFile.value_or("/tmp/haxorg.log")));
    }

    if (opts.loggingFlags.contains(CliOpts::LoggingFlags::LogToStdout)) {
        hstd::log::push_sink(hstd::log::init_stdout_sink());
    }

    HSLOG_INFO("starting");
    HSLOG_TRACE("CLI opts: {}", opts);

    auto pathCB = [](std::string const& path) -> bool {
        // TODO: make this configurable
        if (path.contains(".git") || path.contains(".trunk")) {
            return false;
        } else {
            return true;
        }
    };

    org::parse::ParseContext ctx;
    if (std::holds_alternative<CliOpts::ParseOpts>(opts.cmd)) {
        auto const&    cmd = std::get<CliOpts::ParseOpts>(opts.cmd);
        hstd::fs::path input{cmd.input};

        auto params                = org::parse::OrgParseParameters::shared();
        params->parseTracePath     = cmd.parseTracePath;
        params->baseTokenTracePath = cmd.baseTokenTracePath;
        params->tokenTracePath     = cmd.tokenTracePath;
        params->semTracePath       = cmd.semTracePath;

        auto directoryParsingOpts = org::parse::OrgDirectoryParseParameters::shared();

        directoryParsingOpts->shouldProcessPath = pathCB;

        directoryParsingOpts->getParsedNode =
            [&](std::string const& path) -> org::sem::SemId<org::sem::Org> {
            return ctx.parseFileOpts(path, params);
        };

        if (hstd::fs::is_directory(input)) {
            ctx.parseDirectoryOpts(input, directoryParsingOpts);
        } else {
            if (opts.withIncludes) {
                ctx.parseFileWithIncludes(input, directoryParsingOpts);
            } else {
                ctx.parseFileOpts(input, params);
            }
        }
    } else {
        using EO        = CliOpts::ExportOpts;
        auto const& cmd = std::get<EO>(opts.cmd);


        auto directoryParsingOpts = org::parse::OrgDirectoryParseParameters::shared();

        directoryParsingOpts->shouldProcessPath = pathCB;

        json parse_lefovers_export{};

        auto paramsForPath = [&](std::string const& path) {
            auto params = org::parse::OrgParseParameters::shared();

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
            return ctx.parseFileOpts(path, paramsForPath(path));
        };

        directoryParsingOpts->getParsedNode = pathToNode;

        // TODO: Support multiple inputs and unify all parsed nodes into a single group.
        hstd::fs::path input{cmd.input.at(0)};

        auto node = hstd::fs::is_directory(input)
                      ? ctx.parseDirectoryOpts(input, directoryParsingOpts)
                      : (opts.withIncludes
                             ? ctx.parseFileWithIncludes(input, directoryParsingOpts)
                             : ctx.parseFileOpts(input, paramsForPath(input)));

        auto write_proto_json = [&](google::protobuf::Message const& result) {
            std::string                          json;
            google::protobuf::json::PrintOptions j_opts;
            j_opts.add_whitespace = true;
            auto status           = google::protobuf::util::MessageToJsonString(
                result, &json, j_opts);

            hstd::writeFile(cmd.output, json);
        };


        auto write_proto_binary = [&](google::protobuf::Message const& result) {
            std::ofstream out(cmd.output, std::ios::binary);
            result.SerializeToOstream(&out);
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
                    hstd::writeFile(cmd.output, res.dump(2));
                },
                [&](EO::Yaml const& j) -> void {
                    org::algo::ExporterYaml exp;
                    exp.skipNullFields  = j.skipNullFields;
                    exp.skipFalseFields = j.skipFalseFields;
                    exp.skipZeroFields  = j.skipZeroFields;
                    exp.skipLocation    = j.skipLocation;
                    exp.skipId          = j.skipId;
                    auto res            = exp.evalTop(node.value());
                    hstd::writeFile(cmd.output, fmt::format("{}\n", res));
                },
                [&](EO::Token const& j) -> void {
                    hstd::writeFile(cmd.output, parse_lefovers_export.dump(2));
                },
                [&](EO::BaseToken const& j) -> void {
                    hstd::writeFile(cmd.output, parse_lefovers_export.dump(2));
                },
                [&](EO::ParseNode const& j) -> void {
                    hstd::writeFile(cmd.output, parse_lefovers_export.dump(2));
                },
                [&](EO::Proto const& p) {
                    orgproto::AnyNode result;
                    org::algo::proto_serde<
                        orgproto::AnyNode,
                        org::sem::SemId<org::sem::Org>>::write(&result, node.value());
                    if (p.format == EO::Proto::ProtoFormat::Json) {
                        write_proto_json(result);
                    } else {
                        write_proto_binary(result);
                    }
                },
                [&](EO::Map const& m) {
                    org::graph::MapConfig::Ptr   conf{org::graph::MapConfig::shared()};
                    org::imm::ImmAstContext::Ptr store{
                        org::imm::ImmAstContext::init_start_context()};
                    org::imm::ImmAstVersion version = store->addRoot(node.value());
                    org::graph::MapGraphState::Ptr
                         state   = org::graph::MapGraphState::shared(version.context);
                    auto adapter = version.getRootAdapter();
                    state->addNodeRec(adapter.ctx.lock(), adapter, conf);
                    auto result = state->graph->get_serial();
                    if (m.format == EO::Map::MapFormat::Json) {
                        write_proto_json(*result);
                    } else {
                        write_proto_binary(*result);
                    }
                },
            },
            cmd.data);
    }
}

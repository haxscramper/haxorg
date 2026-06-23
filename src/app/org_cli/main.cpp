#include "haxorg/exporters/ExporterJson.hpp"
#include "haxorg/exporters/exporteryaml.hpp"
#include <boost/describe.hpp>
#include <boost/mp11.hpp>
#include <boost/parser/parser.hpp>
#include <boost/program_options.hpp>
#include <fmt/base.h>
#include <fmt/format.h>
#include <haxorg/api/ParseContext.hpp>
#include <haxorg/lexbase/NodeIO.hpp>
#include <haxorg/test/NodeTest.hpp>
#include <hstd/stdlib/JsonCLIParser.hpp>
#include <optional>
#include <string>
#include <vector>

namespace po = boost::program_options;

struct CliOpts {
    struct ParseOpts {
        /// \brief input file or directory
        std::string            input;
        hstd::Opt<std::string> baseTokenTracePath = std::nullopt;
        hstd::Opt<std::string> tokenTracePath     = std::nullopt;
        hstd::Opt<std::string> parseTracePath     = std::nullopt;
        hstd::Opt<std::string> semTracePath       = std::nullopt;

        ParseOpts() {}
        DESC_FIELDS(ParseOpts, (input, baseTokenTracePath, tokenTracePath, semTracePath));
    };

    struct ExportOpts {
        struct JsonOpts {
            // TODO: Rename the fields to "show empty lists" with default value false.
            bool skipEmptyLists = false;
            bool skipLocation   = false;
            bool skipId         = false;
            bool skipNullFields = false;
            /// \brief Replace multi-character space with a single one on export.
            bool normalizeSpaces = false;
            JsonOpts() {};
            DESC_FIELDS(
                JsonOpts,
                (skipEmptyLists, skipLocation, skipId, skipNullFields, normalizeSpaces));
        };

        struct YamlOpts {
            bool skipNullFields  = false;
            bool skipFalseFields = false;
            bool skipZeroFields  = false;
            bool skipLocation    = false;
            bool skipId          = false;
            DESC_FIELDS(
                YamlOpts,
                (skipNullFields, skipFalseFields, skipZeroFields, skipLocation, skipId));
            YamlOpts() {}
        };

        struct TokenOpts {};
        struct BaseTokenOpts {};
        struct ParseNodesOpts {};

        DECL_DESCRIBED_ENUM(ExportType, JSON, YAML, TOKEN, BASE_TOKEN, PARSE_NODE);

        using ExportTarget = std::
            variant<JsonOpts, YamlOpts, TokenOpts, BaseTokenOpts, ParseNodesOpts>;
        ExportTarget               target;
        std::optional<std::string> exportTrace;
        std::string                input;
        std::string                output;
        ExportOpts() {}
        DESC_FIELDS(ExportOpts, (exportTrace, input, output));
    };

    using MainCmd = std::variant<ParseOpts, ExportOpts>;
    MainCmd cmd;
    bool    withIncludes = true;
    // FIXME: Add sub-variants to the JSON input parsing.
    DESC_FIELDS(CliOpts, (withIncludes));
};


namespace {

[[noreturn]] void exitWithError(std::string const& msg) {
    std::cerr << msg << "\n";
    std::exit(1);
}

CliOpts::ParseOpts parseParseCmd(std::vector<std::string> const& args) {
    CliOpts::ParseOpts opts;

    po::options_description desc("parse options");
    desc.add_options()("help,h", "show help for the parse command")(
        "input",
        po::value<std::string>(&opts.input)->required(),
        "input file or directory")                                                     //
        ("base-token-trace", po::value<std::string>(), "base token trace output path") //
        ("token-trace", po::value<std::string>(), "token trace output path")           //
        ("parse-trace", po::value<std::string>(), "parse trace output path")           //
        ("sem-trace", po::value<std::string>(), "sem trace output path")               //
        ;

    po::positional_options_description pos;
    pos.add("input", 1);

    po::variables_map vm;
    auto parsed = po::command_line_parser(args).options(desc).positional(pos).run();
    po::store(parsed, vm);

    if (vm.count("help")) {
        std::cout << "Usage: parse <input> [options]\n" << desc << "\n";
        std::exit(0);
    }

    po::notify(vm);

    if (vm.count("base-token-trace")) {
        opts.baseTokenTracePath = vm["base-token-trace"].as<std::string>();
    }
    if (vm.count("token-trace")) {
        opts.tokenTracePath = vm["token-trace"].as<std::string>();
    }
    if (vm.count("parse-trace")) {
        opts.parseTracePath = vm["parse-trace"].as<std::string>();
    }
    if (vm.count("sem-trace")) { opts.semTracePath = vm["sem-trace"].as<std::string>(); }

    return opts;
}


CliOpts::ExportOpts::JsonOpts parseJsonOpts(po::variables_map const& vm) {
    CliOpts::ExportOpts::JsonOpts json;
    json.skipEmptyLists  = vm["skip-empty-lists"].as<bool>();
    json.skipLocation    = vm["skip-location"].as<bool>();
    json.skipId          = vm["skip-id"].as<bool>();
    json.skipNullFields  = vm["skip-null-fields"].as<bool>();
    json.normalizeSpaces = vm["normalize-spaces"].as<bool>();
    return json;
}

CliOpts::ExportOpts::YamlOpts parseYamlOpts(po::variables_map const& vm) {
    CliOpts::ExportOpts::YamlOpts yaml;
    yaml.skipNullFields  = vm["skip-null-fields"].as<bool>();
    yaml.skipFalseFields = vm["skip-false-fields"].as<bool>();
    yaml.skipZeroFields  = vm["skip-zero-fields"].as<bool>();
    yaml.skipLocation    = vm["skip-location"].as<bool>();
    yaml.skipId          = vm["skip-id"].as<bool>();
    return yaml;
}

CliOpts::ExportOpts parseExportCmd(std::vector<std::string> const& args) {
    if (args.empty()) {
        exitWithError("export: missing export type (expected 'json' or 'yaml')");
    }

    CliOpts::ExportOpts::ExportType type;
    std::string const&              typeStr = args.front();
    if (typeStr == "json") {
        type = CliOpts::ExportOpts::ExportType::JSON;
    } else if (typeStr == "yaml") {
        type = CliOpts::ExportOpts::ExportType::YAML;
    } else if (typeStr == "-h" || typeStr == "--help") {
        std::cout << "Usage: export <json|yaml> <input> <output> [options]\n";
        std::exit(0);
    } else {
        exitWithError(
            "export: unknown export type '" + typeStr + "' (expected 'json' or 'yaml')");
    }

    std::vector<std::string> rest(args.begin() + 1, args.end());

    CliOpts::ExportOpts opts;

    po::options_description common("export options");
    common.add_options()                                                             //
        ("help,h", "show help for the export command")                               //
        ("input", po::value<std::string>(&opts.input)->required(), "input org file") //
        ("output", po::value<std::string>(&opts.output)->required(), "output file")  //
        ("export-trace", po::value<std::string>(), "export trace path");


    po::options_description jsonDesc("json options");
    jsonDesc.add_options() //
        ("skip-empty-lists",
         po::value<bool>()->default_value(true),
         "skip empty lists on export") //
        ("skip-location",
         po::value<bool>()->default_value(true),
         "skip location fields") //
        ("skip-id",
         po::value<bool>()->default_value(true),
         "skip id fields") //
        ("skip-null-fields",
         po::value<bool>()->default_value(true),
         "skip null fields") //
        ("normalize-spaces",
         po::value<bool>()->default_value(true),
         "replace multi-character space with a single one") //
        ;

    po::options_description yamlDesc("yaml options");
    yamlDesc.add_options()(
        "skip-null-fields", po::value<bool>()->default_value(true), "skip null fields") //
        ("skip-false-fields",
         po::value<bool>()->default_value(true),
         "skip false fields") //
        ("skip-zero-fields",
         po::value<bool>()->default_value(true),
         "skip zero fields") //
        ("skip-location",
         po::value<bool>()->default_value(true),
         "skip location fields")                                              //
        ("skip-id", po::value<bool>()->default_value(true), "skip id fields") //
        ;

    po::options_description desc;
    desc.add(common);
    if (type == CliOpts::ExportOpts::ExportType::JSON) {
        desc.add(jsonDesc);
    } else {
        desc.add(yamlDesc);
    }

    po::positional_options_description pos;
    pos.add("input", 1);
    pos.add("output", 1);

    po::variables_map vm;
    auto parsed = po::command_line_parser(rest).options(desc).positional(pos).run();
    po::store(parsed, vm);

    if (vm.count("help")) {
        std::cout << "Usage: export " << typeStr << " <input> <output> [options]\n"
                  << desc << "\n";
        std::exit(0);
    }

    po::notify(vm);

    if (vm.count("export-trace")) {
        opts.exportTrace = vm["export-trace"].as<std::string>();
    }

    if (type == CliOpts::ExportOpts::ExportType::JSON) {
        opts.target = parseJsonOpts(vm);
    } else {
        opts.target = parseYamlOpts(vm);
    }

    return opts;
}

} // namespace

CliOpts parseCli(int argc, char** argv) {
    if (argc < 2) {
        exitWithError(
            "missing command\n"
            "Usage: <program> <parse|export> ...\n"
            "  parse  <input>\n"
            "  export <json|yaml> <input> <output>");
    }

    std::string const        cmd = argv[1];
    std::vector<std::string> rest(argv + 2, argv + argc);

    CliOpts result;

    // strip the root-level --with-includes option out of `rest` so the
    // subcommand parsers don't choke on it
    po::options_description rootDesc;
    rootDesc.add_options()                                                    //
        ("with-includes", po::value<bool>(), "parse input with all includes") //
        ;

    po::variables_map rootVm;
    auto              parsedRoot = po::command_line_parser(rest)
                                       .options(rootDesc)
                                       .allow_unregistered()
                                       .run();
    po::store(parsedRoot, rootVm);
    po::notify(rootVm);

    if (rootVm.count("with-includes")) {
        result.withIncludes = rootVm["with-includes"].as<bool>();
    }

    rest = po::collect_unrecognized(parsedRoot.options, po::include_positional);

    if (cmd == "parse") {
        result.cmd = parseParseCmd(rest);
    } else if (cmd == "export") {
        result.cmd = parseExportCmd(rest);
    } else if (cmd == "-h" || cmd == "--help") {
        std::cout << "Usage: <program> <parse|export> ...\n"
                     "  parse  <input>\n"
                     "  export <json|yaml> <input> <output>\n";
        std::exit(0);
    } else {
        exitWithError("unknown command '" + cmd + "' (expected 'parse' or 'export')");
    }

    return result;
}

int main(int argc, char* argv[]) {
    auto opts //
        = argc == 2 && std::string{argv[1]}.starts_with("/")
            ? hstd::parse_json_argc<CliOpts>(argc, argv)
            : parseCli(argc, argv);

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
        auto const& cmd = std::get<CliOpts::ExportOpts>(opts.cmd);


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
                    [&](CliOpts::ExportOpts::TokenOpts const& j) -> void {
                        params->onTokenizerDone =
                            [&](org::parse::OrgTokenGroup const& tokens,
                                std::optional<int>               fragmentIndex) {
                                parse_lefovers_export["tokenizer_export"].push_back(
                                    group_json_repr(tokens, fragmentIndex));
                            };
                    },
                    [&](CliOpts::ExportOpts::BaseTokenOpts const& j) -> void {
                        params->onBaseTokenizeDone =
                            [&](org::parse::OrgTokenGroup const& tokens,
                                std::optional<int>               fragmentIndex) {
                                parse_lefovers_export["base_tokenizer_export"].push_back(
                                    group_json_repr(tokens, fragmentIndex));
                            };
                    },
                    [&](CliOpts::ExportOpts::ParseNodesOpts const& j) -> void {
                        params->onParseDone = [&](org::parse::OrgNodeGroup const& tokens,
                                                  std::optional<int> fragmentIndex) {
                            parse_lefovers_export["parse_export"].push_back(
                                group_json_repr(tokens, fragmentIndex));
                        };
                    },
                    [&](auto const& j) -> void {},
                },
                cmd.target);

            return params;
        };

        auto pathToNode = [&](std::string const& path) -> org::sem::SemId<org::sem::Org> {
            return ctx.parseFileOpts(path, paramsForPath(path));
        };

        directoryParsingOpts->getParsedNode = pathToNode;

        hstd::fs::path input{cmd.input};

        auto node = hstd::fs::is_directory(input)
                      ? ctx.parseDirectoryOpts(input, directoryParsingOpts)
                      : (opts.withIncludes
                             ? ctx.parseFileWithIncludes(input, directoryParsingOpts)
                             : ctx.parseFileOpts(input, paramsForPath(input)));

        std::visit(
            hstd::overloaded{
                [&](CliOpts::ExportOpts::JsonOpts const& j) -> void {
                    org::algo::ExporterJson exp;
                    exp.skipEmptyLists  = j.skipEmptyLists;
                    exp.skipId          = j.skipId;
                    exp.skipLocation    = j.skipLocation;
                    exp.skipNullFields  = j.skipNullFields;
                    exp.normalizeSpaces = j.normalizeSpaces;
                    auto res            = exp.evalTop(node.value());
                    hstd::writeFile(cmd.output, res.dump(2));
                },
                [&](CliOpts::ExportOpts::YamlOpts const& j) -> void {
                    org::algo::ExporterYaml exp;
                    exp.skipNullFields  = j.skipNullFields;
                    exp.skipFalseFields = j.skipFalseFields;
                    exp.skipZeroFields  = j.skipZeroFields;
                    exp.skipLocation    = j.skipLocation;
                    exp.skipId          = j.skipId;
                    auto res            = exp.evalTop(node.value());
                    hstd::writeFile(cmd.output, fmt::format("{}\n", res));
                },
                [&](CliOpts::ExportOpts::TokenOpts const& j) -> void {
                    hstd::writeFile(cmd.output, parse_lefovers_export.dump(2));
                },
                [&](CliOpts::ExportOpts::BaseTokenOpts const& j) -> void {
                    hstd::writeFile(cmd.output, parse_lefovers_export.dump(2));
                },
                [&](CliOpts::ExportOpts::ParseNodesOpts const& j) -> void {
                    hstd::writeFile(cmd.output, parse_lefovers_export.dump(2));
                },
            },
            cmd.target);
    }
}

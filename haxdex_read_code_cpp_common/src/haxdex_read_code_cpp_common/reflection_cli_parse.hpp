#pragma once

#include <hstd_cpp_lib/logger/logger.hpp>
#include <hstd_cpp_lib/stdlib/Filesystem.hpp>
#include <hstd_cpp_lib/stdlib/formatting/specializations/VecFormatter.hpp>

#include <haxdex_read_code_cpp_common/reflection_config.hpp>

inline ReflectionCLI parse_reflection_cli(int argc, char const** argv) {
    if (argc != 2) {
        std::vector<std::string> argv_v;
        for (int i = 0; i < argc; ++i) {
            argv_v.push_back(fmt::format("\n '{}'", argv[i]));
        }

        throw hstd::runtime_error::init(
            fmt::format(
                "Expected exactly one CLI argument: JSON literal for the "
                "configuration or a path to the JSON file. argc={} "
                "argv={}",
                argc,
                argv_v));
    }

    std::string json_parameters;
    if (std::string{argv[1]}.starts_with("/")) {
        if (!hstd::fs::exists(argv[1])) {
            throw std::logic_error(
                fmt::format("Input configuration file '{}' does not exist", argv[1]));
        }
        json_parameters = hstd::readFile(argv[1]);
    } else {
        json_parameters = std::string{argv[1]};
    }

    auto cli = hstd::JsonSerde<ReflectionCLI>::from_json(json::parse(json_parameters));

    if (cli.output.empty()) {
        throw hstd::invalid_argument::init(
            "Missing 'output' field in the CLI configuration.");
    }

    if (cli.log_path) {
        hstd::log::push_sink(hstd::log::init_file_sink(cli.log_path.value()));
        HSLOG_INFO("Log file message");
    }

    return cli;
}

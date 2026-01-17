#pragma once

#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Exception.hpp>
#include <hstd/stdlib/JsonSerde.hpp>

namespace hstd {
template <typename T>
T parse_json_argc(int argc, char const** argv) {
    if (argc != 2) {
        std::vector<std::string> argv_v;
        for (int i = 0; i < argc; ++i) {
            argv_v.push_back(std::format("\n '{}'", argv[i]));
        }

        throw hstd::runtime_error::init(
            std::format(
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
                std::format(
                    "Input configuration file '{}' does not exist",
                    argv[1]));
        }
        json_parameters = hstd::readFile(argv[1]);
    } else {
        json_parameters = std::string{argv[1]};
    }

    return hstd::JsonSerde<T>::from_json(json::parse(json_parameters));
}

template <typename T>
T parse_json_argc(int argc, char** argv) {
    return parse_json_argc<T>(argc, const_cast<char const**>(argv));
}
} // namespace hstd

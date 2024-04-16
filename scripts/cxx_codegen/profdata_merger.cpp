#include <llvm/Support/VirtualFileSystem.h>
#include <llvm/ProfileData/InstrProfReader.h>
#include <llvm/Support/Error.h>
#include <llvm/Support/JSON.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/CommandLine.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

std::string read_file(fs::path const& path) {
    std::ifstream     file{path.native()};
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::ostream& LOG(std::string const& msg, int line = __builtin_LINE()) {
    return std::cerr << std::format("[profmerge] {} {}\n ", line, msg);
}


int main(int argc, char** argv) {
    if (argc != 2) {
        LOG("Expected single positional argument -- JSON literal "
            "with parameters or absolute path to the JSON "
            "configuration file.");
        return 1;
    }

    std::string json_parameters;
    if (std::string{argv[1]}.starts_with("/")) {
        json_parameters = read_file(argv[1]);
    } else {
        json_parameters = std::string{argv[1]};
    }

    llvm::Expected<llvm::json::Value> parsed = llvm::json::parse(
        json_parameters);

    if (!parsed) {
        LOG(std::format(
            "Failed to parse JSON: {}\n{}",
            toString(parsed.takeError()),
            json_parameters));
        return 1;
    }

    llvm::Expected<llvm::json::Value> summary = llvm::json::parse(
        read_file(parsed->getAsObject()->getString("coverage")->str()));

    auto FS = llvm::vfs::getRealFileSystem();
    for (auto const& run : *summary->getAsObject()->getArray("runs")) {
        std::string coverage_path = run.getAsObject()
                                        ->getString("test_profile")
                                        ->str();

        auto ReaderOr = llvm::InstrProfReader::create(coverage_path, *FS);
        if (llvm::Error E = ReaderOr.takeError()) {
            LOG(std::format(
                "Error reading profile data from {}: {}",
                coverage_path,
                toString(std::move(E))));
            return 1;
        } else {
            LOG(std::format("Coverage path {} ok", coverage_path));
        }
    }
}

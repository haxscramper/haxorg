#include <llvm/Support/VirtualFileSystem.h>
#include <llvm/ProfileData/InstrProfReader.h>
#include <llvm/Support/Error.h>
#include <llvm/Support/JSON.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/CommandLine.h>
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Expected single positional argument -- JSON literal "
                     "with parameters or absolute path to the JSON "
                     "configuration file.";
        return 1;
    }

    std::string json_parameters;
    if (fs::is_fifo(argv[1])) {
        std::ifstream file{argv[1]};
        file >> json_parameters;
    } else {
        json_parameters = std::string{argv[1]};
    }

    llvm::Expected<llvm::json::Value> parsed = llvm::json::parse(
        json_parameters);

    if (!parsed) {
        llvm::errs() << "Failed to parse JSON: " << parsed.takeError()
                     << "\n";
        return 1;
    }

    auto FS = llvm::vfs::getRealFileSystem();
    for (auto const& ProfPath :
         *parsed->getAsObject()->getArray("coverage")) {
        std::ifstream file{ProfPath.getAsString()->str()};
        std::string   content;
        file >> content;
        auto        cookie        = llvm::json::parse(content);
        std::string coverage_path = cookie->getAsObject()
                                        ->getString("path")
                                        ->str();

        auto ReaderOr = llvm::InstrProfReader::create(coverage_path, *FS);
        if (llvm::Error E = ReaderOr.takeError()) {
            std::cerr << "Error reading profile data from "
                      << coverage_path << ": " << toString(std::move(E))
                      << "\n";
            return 1;
        }
    }
}

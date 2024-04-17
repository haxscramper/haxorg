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
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/ProfileData/InstrProfReader.h>
#include <llvm/ProfileData/InstrProfWriter.h>
#include <llvm/ProfileData/Coverage/CoverageMappingReader.h>


namespace fs = std::filesystem;
using namespace llvm;
using namespace llvm::coverage;

std::string read_file(fs::path const& path) {
    std::ifstream     file{path.native()};
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::ostream& LOG(std::string const& msg, int line = __builtin_LINE()) {
    return std::cerr << std::format("[profmerge:{}] {}\n", line, msg);
}


static void loadInput(
    std::string const& Filename,
    std::string const& ProfiledBinary,
    InstrProfWriter*   Writer) {

    auto FS          = vfs::getRealFileSystem();
    auto ReaderOrErr = InstrProfReader::create(Filename, *FS);
    if (Error E = ReaderOrErr.takeError()) {
        auto [ErrCode, Msg] = InstrProfError::take(std::move(E));
        if (ErrCode != instrprof_error::empty_raw_profile) {
            assert(false);
        }
        return;
    }

    auto Reader = std::move(ReaderOrErr.get());
    for (auto& I : *Reader) {
        const StringRef FuncName = I.Name;
        bool            Reported = false;
        Writer->addRecord(std::move(I), 1, [&](Error E) {
            LOG(std::format("{}", toString(std::move(E))));
        });
    }

    if (Reader->hasTemporalProfile()) {
        auto& Traces = Reader->getTemporalProfTraces();
        if (!Traces.empty()) {
            Writer->addTemporalProfileTraces(
                Traces, Reader->getTemporalProfTraceStreamSize());
        }
    }

    if (Reader->hasError()) {
        if (Error E = Reader->getError()) {
            LOG(std::format("{} {}", toString(std::move(E)), Filename));
            return;
        }
    }

    std::vector<object::BuildID> BinaryIds;
    if (Error E = Reader->readBinaryIds(BinaryIds)) {
        LOG(std::format("{} {}", toString(std::move(E)), Filename));
        return;
    }

    Writer->addBinaryIds(BinaryIds);
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

    Expected<json::Value> parsed = json::parse(json_parameters);

    if (!parsed) {
        LOG(std::format(
            "Failed to parse JSON: {}\n{}",
            toString(parsed.takeError()),
            json_parameters));
        return 1;
    }

    Expected<json::Value> summary = json::parse(
        read_file(parsed->getAsObject()->getString("coverage")->str()));

    auto FS = vfs::getRealFileSystem();
    for (auto const& run : *summary->getAsObject()->getArray("runs")) {
        std::string coverage_path = run.getAsObject()
                                        ->getString("test_profile")
                                        ->str();

        std::string binary_path = run.getAsObject()
                                      ->getString("test_binary")
                                      ->str();


        InstrProfWriter Writer;
        loadInput(coverage_path, binary_path, &Writer);
        LOG(std::format(
            "Loaded {} binary {}", coverage_path, binary_path));

        std::vector<StringRef> ObjectFilenames;
        ObjectFilenames.push_back(binary_path);

        std::string tmp_path = "/tmp/tmp.profdata";

        {
            std::error_code EC;
            raw_fd_ostream  Output(tmp_path, EC, sys::fs::OF_None);

            if (EC) {
                LOG(std::format(
                    "Error while creating output stream {}",
                    EC.message()));
                return 1;
            }

            if (Error E = Writer.write(Output)) {
                LOG(std::format(
                    "Failed write: {}", toString(std::move(E))));
                return 1;
            }
        }

        auto FS = vfs::getRealFileSystem();
        Expected<std::unique_ptr<CoverageMapping>>
            mapping_or_err = CoverageMapping::load(
                ObjectFilenames, tmp_path, *FS);

        if (Error E = mapping_or_err.takeError()) {
            LOG(std::format(
                "Failed to load profdata {}", toString(std::move(E))));
            return 1;
        }

        auto const& mapping = mapping_or_err.get();

        for (auto const& f : mapping->getCoveredFunctions()) {
            LOG(std::format("{}", f.Name));
        }
    }
}

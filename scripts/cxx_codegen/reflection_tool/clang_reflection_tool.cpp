#include "clang_reflection_lib.hpp"
#include "hstd/stdlib/Filesystem.hpp"
#include "hstd/stdlib/JsonSerde.hpp"

#include <clang/Tooling/ArgumentsAdjusters.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/Tooling.h>
#include <llvm/Support/CommandLine.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/JSONCompilationDatabase.h>
#include <filesystem>
#include <format>
#include <llvm/Support/JSON.h>
#include <fstream>
#include <format>

namespace fs = std::filesystem;

static clang::ParsedAttrInfoRegistry::Add<ExampleAttrInfo> Z(
    REFL_NAME,
    "example attribute description");

static llvm::cl::OptionCategory ToolingSampleCategory(
    "Generate reflection data");

llvm::cl::opt<std::string> CompilationDB(
    "compilation-database",
    llvm::cl::desc("Compilation database"),
    llvm::cl::cat(ToolingSampleCategory));

llvm::cl::opt<std::string> RunMode(
    "run-mode",
    llvm::cl::desc("Specify tool execution mode"),
    llvm::cl::value_desc("Run mode: TranslationUnit, BinarySymbols"),
    llvm::cl::cat(ToolingSampleCategory));

llvm::cl::opt<std::string> outputPathOverride(
    "out",
    llvm::cl::desc("Specify output path"),
    llvm::cl::value_desc("output path"),
    llvm::cl::cat(ToolingSampleCategory));

llvm::cl::opt<std::string> ToolchainInclude(
    "toolchain-include",
    llvm::cl::desc("Path to the LLVM Toolchain include directory"),
    llvm::cl::cat(ToolingSampleCategory));

llvm::cl::opt<bool> VerboseRun(
    "verbose",
    llvm::cl::desc("Run compilation in verbose mode"),
    llvm::cl::cat(ToolingSampleCategory));

llvm::cl::opt<bool> MainTuAnalysis(
    "main-tu-analysis",
    llvm::cl::desc(
        "Analyze all files references in the compilation database"),
    llvm::cl::cat(ToolingSampleCategory));


llvm::cl::opt<bool> NoStdInc(
    "nostdinc",
    llvm::cl::desc("No STD include"),
    llvm::cl::cat(ToolingSampleCategory));

llvm::cl::opt<std::string> TargetFiles(
    "target-files",
    llvm::cl::desc("Single input file or file with json array, list of "
                   "absolute paths whose "
                   "declarations will be included into TU dump."),
    llvm::cl::cat(ToolingSampleCategory));

std::vector<std::string> parseTargetFiles(std::string path) {
    std::ifstream ifs{path};
    if (!ifs.is_open()) {
        throw std::domain_error(std::format(
            "Failed to open the target file list: '{}', {}",
            path,
            std::strerror(errno)));
    }

    if (!path.ends_with("json")) { return {path}; }

    std::string jsonContent(
        (std::istreambuf_iterator<char>(ifs)),
        (std::istreambuf_iterator<char>()));

    llvm::Expected<llvm::json::Value> parsed = llvm::json::parse(
        jsonContent);

    if (!parsed) {
        throw std::domain_error(std::format(
            "Failed to parse error {}",
            llvm::toString(parsed.takeError())));
    }

    llvm::json::Array* arr = parsed->getAsArray();
    if (!arr) { throw std::domain_error("JSON is not an array"); }

    std::vector<std::string> result;
    for (auto& val : *arr) {
        if (val.kind() != llvm::json::Value::String) {
            throw std::domain_error("Array element is not a string");
        }
        result.push_back(val.getAsString()->str());
    }

    return result;
}


std::ostream& LOG_CERR(int line = __builtin_LINE()) {
    return std::cerr << std::format("[clang-reflect] {} ", line);
}


class ReflFrontendAction : public clang::ASTFrontendAction {
  protected:
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
        clang::CompilerInstance& CI,
        llvm::StringRef) override {
        LOG_CERR() << "Ast consumer verbose: " << VerboseRun.getValue()
                   << std::endl;
        auto consumer = std::make_unique<ReflASTConsumer>(
            CI, VerboseRun.getValue());
        if (!outputPathOverride.empty()) {
            consumer->outputPathOverride = outputPathOverride;
        }

        if (TargetFiles.empty()) {
            if (MainTuAnalysis) {
                consumer->Visitor.visitMode = ReflASTVisitor::VisitMode::
                    AllMainTranslationUnit;
            } else {
                consumer->Visitor.visitMode = ReflASTVisitor::VisitMode::
                    AllAnnotated;
            }
        } else {
            std::vector files = parseTargetFiles(TargetFiles.getValue());
            for (auto const& file : files) {
                LOG_CERR() << "Target file " << file << std::endl;
            }
            consumer->Visitor.targetFiles.insert(
                files.begin(), files.end());

            consumer->Visitor.visitMode = ReflASTVisitor::VisitMode::
                AllTargeted;
        }

        return consumer;
    }
};

/// Filter out compilation options that were used in the compilation
/// database -- remove reflection plugin usage, precompiled headers, and
/// add provided toolchain include configuration.
clang::tooling::CommandLineArguments dropReflectionPLugin(
    const clang::tooling::CommandLineArguments& Args,
    llvm::StringRef                             Filename) {
    clang::tooling::CommandLineArguments filteredArgs;

    auto push = [&](std::string const& value,
                    int                line = __builtin_LINE()) {
        if (VerboseRun) {
            LOG_CERR(line) << "+++ Adding " << value << std::endl;
        }
        filteredArgs.push_back(value);
    };

    for (size_t i = 0; i < Args.size(); ++i) {
        auto drop = [&](int line = __builtin_LINE()) {
            if (VerboseRun) {
                LOG_CERR(line)
                    << "!!! Discarding " << Args[i] << std::endl;
            }
        };

        // Skip unwanted arguments
        if (Args[i] == "-Xclang" && (i + 1 < Args.size())
            && (Args[i + 1] == "-add-plugin"
                || Args[i + 1] == "refl-plugin"
                || Args[i + 1].starts_with("out=")
                || Args[i + 1] == "-plugin-arg-refl-plugin")) {

            i++;
            drop();
        } else if (Args[i].find("-fplugin=") != std::string::npos) {
            drop();
        } else if (Args[i].find("sarif") != std::string::npos) {
            drop();
        } else if (
            Args[i].starts_with("@")
            || Args[i].starts_with("-vectorize")) {
            drop();
        } else if (
            Args[i].starts_with("-W") && !Args[i].starts_with("-Wno")) {
            drop();
        } else if (
            (i + 3 < Args.size())   //
            && Args[i] == "-Xclang" //
            && (Args[i + 1] == "-include-pch"
                || Args[i + 1] == "-include") //
            && Args[i + 2] == "-Xclang"       //
            && (Args[i + 3].ends_with("pch")
                || Args[i + 3].find("cmake_pch") != std::string::npos)) {
            drop();
            ++i;
            drop();
            ++i;
            drop();
            ++i;
            drop();

        } else {
            push(Args[i]);
        }
    }

    // TODO Redirect warnings and other diagnostics into a temporary
    // location Use serif output.
    push("-Wno-everything");
    if (VerboseRun) { push("-v"); }
    push("-isystem");
    push(ToolchainInclude);
    /*
     * Clang with custom LLVM toolchain is able to find toolchain include
     * correctly and append it to the path, but with this separate tool the
     * order of includes is wrong. It puts `ToolchainInclude` first and
     * then there are duplicates of C++-specific include headers.
     *
     * The desired order is -- doing it the other way around triggers
     * explicit ordering guards in the cstddef.
     *
     * ```
     * llvm/include/c++/v1
     * llvm/include/x86_64-unknown-linux-gnu/c++/v1
     * llvm/lib/clang/17/include
     * ```
     *
     * The ordering above satisfies check from c++/v1/cstddef:43
     *
     * ```
     * #include <stddef.h>
     * #ifndef _LIBCPP_STDDEF_H
     * #   error <cstddef> tried including <stddef.h> but didn't find libc++'s <stddef.h> header. \
     * #endif
     * ```
     *
     * I have a high confidence that the whole approach of CLI argument
     * rewriting here is not correct and instead I need to convince the
     * reflection tool to actually construct the default stdinc++ path
     * correctly right away, but at the moment whatever I wrote also works.
     */
    if (NoStdInc) { push("-nostdinc++"); }
    // NOTE: The comment above was relevant when the custom standard
    // library was used in the build process. When the system-provided one
    // is used it does not seem to be required (on the contrary, removing
    // std include causes issues with `cstdddef`), but the message above
    // should stay there regardless.

    if (VerboseRun) {
        LOG_CERR() << "Filtered command line arguments\n";
        for (auto const& arg : filteredArgs) {
            LOG_CERR() << "[ ] " << arg << "\n";
        }

        LOG_CERR() << ":: ";
        for (auto const& arg : filteredArgs) { std::cerr << " " << arg; }
        std::cerr << "\n";
    }

    return filteredArgs;
}


int main(int argc, const char** argv) {
    auto cli = clang::tooling::CommonOptionsParser::create(
        argc, argv, ToolingSampleCategory, llvm::cl::ZeroOrMore);

    if (!cli) {
        LOG_CERR() << "CLI is invalid" << std::endl;
        llvm::errs() << cli.takeError();
        return 1;
    }


    if (RunMode == "TranslationUnit") {
        clang::tooling::CommonOptionsParser& OptionsParser = cli.get();
        std::string                          ErrorMessage;

        auto JSONDB = clang::tooling::JSONCompilationDatabase::
            loadFromFile(
                CompilationDB,
                ErrorMessage,
                clang::tooling::JSONCommandLineSyntax::AutoDetect);

        if (!JSONDB) {
            LOG_CERR()
                << "Failed to process provided JSON DB, failure was:"
                << std::endl;
            LOG_CERR() << ErrorMessage << std::endl;
            LOG_CERR() << "CompilationDB = " << CompilationDB << std::endl;
            return 1;
        } else {
            LOG_CERR() << "Using compilation database " << CompilationDB
                       << "\n";
        }

        clang::tooling::ArgumentsAdjustingCompilations
            adjustedCompilations(std::move(JSONDB));

        adjustedCompilations.appendArgumentsAdjuster(dropReflectionPLugin);

        clang::tooling::ClangTool tool(
            adjustedCompilations, OptionsParser.getSourcePathList());

        if (!ToolchainInclude.empty()) {
            if (!fs::is_directory(std::string(ToolchainInclude))) {
                LOG_CERR()
                    << "Toolchain include is not a directory or does "
                       "not exist '"
                    << ToolchainInclude << "'\n";
                return 1;
            }
        }

        if (VerboseRun) {
            LOG_CERR() << "Using toolchain include " << ToolchainInclude
                       << std::endl;

            LOG_CERR() << "Configuration parse OK, running tool\n";
        }
        int result = tool.run(
            clang::tooling::newFrontendActionFactory<ReflFrontendAction>()
                .get());

        return result;
    } else if (RunMode == "BinarySymbols") {

        if (outputPathOverride.empty()) {
            throw std::invalid_argument(
                std::format("Missing output path, specify with --out"));
        }

        auto sections = getSymbolsInBinary(
            parseTargetFiles(TargetFiles).at(0));

        hstd::writeFile(
            outputPathOverride.getValue(),
            hstd::to_json_eval(sections).dump(2));

        return 0;

    } else {
        throw std::invalid_argument(std::format(
            "Run mode is expected to be 'TranslationUnit' or "
            "'BinarySymbols', but found '{}'",
            RunMode.getValue()));
    }
}

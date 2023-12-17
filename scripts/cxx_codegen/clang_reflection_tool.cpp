#include "clang_reflection_lib.hpp"


#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/Tooling.h>
#include <llvm/Support/CommandLine.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/JSONCompilationDatabase.h>
import std;
import std;
#include <llvm/Support/JSON.h>

namespace fs = std::filesystem;

static clang::ParsedAttrInfoRegistry::Add<ExampleAttrInfo> Z(
    REFL_NAME,
    "example attribute description");

static llvm::cl::OptionCategory ToolingSampleCategory(
    "Generate reflection data");

llvm::cl::opt<std::string> CompilationDB(
    "compilation-database",
    llvm::cl::desc("Compilation database"),
    llvm::cl::Required,
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

llvm::cl::opt<std::string> TargetFiles(
    "target-files",
    llvm::cl::desc("File with json array, list of absolute paths whose "
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
    if (!arr) {
        throw std::domain_error("JSON is not an array");
    }

    std::vector<std::string> result;
    for (auto& val : *arr) {
        if (val.kind() != llvm::json::Value::String) {
            throw std::domain_error("Array element is not a string");
        }
        result.push_back(val.getAsString()->str());
    }

    return result;
}


class ReflFrontendAction : public clang::ASTFrontendAction {
  protected:
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
        clang::CompilerInstance& CI,
        llvm::StringRef) override {
        auto consumer = std::make_unique<ReflASTConsumer>(CI);
        if (!outputPathOverride.empty()) {
            consumer->outputPathOverride = outputPathOverride;
        }
        if (TargetFiles.empty()) {
            consumer->Visitor.visitMode = ReflASTVisitor::VisitMode::
                AllAnnotated;
        } else {
            std::vector files = parseTargetFiles(TargetFiles.getValue());
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
    for (size_t i = 0; i < Args.size(); ++i) {
        // Skip unwanted arguments
        if (Args[i] == "-Xclang" && (i + 1 < Args.size())
            && (Args[i + 1] == "-add-plugin"
                || Args[i + 1] == "refl-plugin"
                || Args[i + 1].starts_with("out=")
                || Args[i + 1] == "-plugin-arg-refl-plugin")) {
            i++;
        } else if (Args[i].find("-fplugin=") != std::string::npos) {
        } else if (Args[i].starts_with("@")) {
        } else if (
            Args[i].starts_with("-W") && !Args[i].starts_with("-Wno")) {
        } else if (
            (i + 3 < Args.size())   //
            && Args[i] == "-Xclang" //
            && (Args[i + 1] == "-include-pch"
                || Args[i + 1] == "-include") //
            && Args[i + 2] == "-Xclang"       //
            && (Args[i + 3].ends_with("pch")
                || Args[i + 3].find("cmake_pch") != std::string::npos)) {
            i += 3;

        } else {
            filteredArgs.push_back(Args[i]);
        }
    }

    // TODO Redirect warnings and other diagnostics into a temporary
    // location Use serif output.
    filteredArgs.push_back("-Wno-everything");
    filteredArgs.push_back("-isystem");
    filteredArgs.push_back(ToolchainInclude);

    return filteredArgs;
}


int main(int argc, const char** argv) {
    auto cli = clang::tooling::CommonOptionsParser::create(
        argc, argv, ToolingSampleCategory);

    if (!cli) {
        llvm::errs() << cli.takeError();
        return 1;
    }

    clang::tooling::CommonOptionsParser& OptionsParser = cli.get();
    std::string                          ErrorMessage;

    auto JSONDB = clang::tooling::JSONCompilationDatabase::loadFromFile(
        CompilationDB,
        ErrorMessage,
        clang::tooling::JSONCommandLineSyntax::AutoDetect);

    if (!JSONDB) {
        llvm::errs() << ErrorMessage;
        return 1;
    }

    clang::tooling::ArgumentsAdjustingCompilations adjustedCompilations(
        std::move(JSONDB));

    adjustedCompilations.appendArgumentsAdjuster(dropReflectionPLugin);

    clang::tooling::ClangTool tool(
        adjustedCompilations, OptionsParser.getSourcePathList());

    if (!ToolchainInclude.empty()) {
        if (!fs::is_directory(std::string(ToolchainInclude))) {
            llvm::errs() << "Toolchain include is not a directory or does "
                            "not exist '"
                         << ToolchainInclude << "'\n";
            return 1;
        }
    }

    int result = tool.run(
        clang::tooling::newFrontendActionFactory<ReflFrontendAction>()
            .get());

    return result;
}

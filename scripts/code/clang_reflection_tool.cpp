#include "clang_reflection_lib.hpp"


#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/Tooling.h>
#include <llvm/Support/CommandLine.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/JSONCompilationDatabase.h>

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


class ReflFrontendAction : public clang::ASTFrontendAction {
  protected:
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
        clang::CompilerInstance& CI,
        llvm::StringRef) override {
        auto consumer = std::make_unique<ReflASTConsumer>(CI);
        if (!outputPathOverride.empty()) {
            consumer->outputPathOverride = outputPathOverride;
        }
        return consumer;
    }
};

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


    for (auto const& arg : filteredArgs) {
        llvm::outs() << arg << " ";
    }

    llvm::outs() << "\n";
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

    int result = tool.run(
        clang::tooling::newFrontendActionFactory<ReflFrontendAction>()
            .get());

    return result;
}

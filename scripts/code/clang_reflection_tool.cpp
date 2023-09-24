#include "clang_reflection_lib.hpp"


#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/Tooling.h>
#include <llvm/Support/CommandLine.h>
#include <clang/Tooling/CommonOptionsParser.h>

llvm::cl::opt<std::string> outputPathOverride(
    "out",
    llvm::cl::desc("Specify output path"),
    llvm::cl::value_desc("output path"));


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

static llvm::cl::OptionCategory ToolingSampleCategory(
    "Refactor T const& to CR<T>");

int main(int argc, const char** argv) {
    auto cli = clang::tooling::CommonOptionsParser::create(
        argc, argv, ToolingSampleCategory);

    if (!cli) {
        llvm::errs() << cli.takeError();
        return 1;
    }

    clang::tooling::CommonOptionsParser& OptionsParser = cli.get();
    clang::tooling::ClangTool tool(
        OptionsParser.getCompilations(),
        OptionsParser.getSourcePathList());

    int result = tool.run(
        clang::tooling::newFrontendActionFactory<ReflFrontendAction>()
            .get());

    return result;
}

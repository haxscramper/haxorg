#include <llvm/Support/TimeProfiler.h>

#include "clang_reflection_lib.hpp"

static clang::ParsedAttrInfoRegistry::Add<ExampleAttrInfo> Z(
    REFL_NAME,
    "example attribute description");


class ReflPluginAction : public clang::PluginASTAction {
  protected:
    std::optional<std::string>          outputPathOverride;
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
        clang::CompilerInstance& CI,
        llvm::StringRef) override {

        auto tmp                = std::make_unique<ReflASTConsumer>(CI, false);
        tmp->outputPathOverride = outputPathOverride;
        return tmp;
    }


    bool ParseArgs(
        const clang::CompilerInstance&  CI,
        const std::vector<std::string>& args) override {
        for (auto const& arg : args) {
            if (arg.starts_with("out=")) {
                outputPathOverride = arg.substr(strlen("out="));
            }
        }
        return true;
    }


  public:
    ReflPluginAction() {}

    ActionType getActionType() override {
        return ActionType::CmdlineAfterMainAction;
    }
};

static clang::FrontendPluginRegistry::Add<ReflPluginAction> X(
    "refl-plugin",
    "Reflection plugin");

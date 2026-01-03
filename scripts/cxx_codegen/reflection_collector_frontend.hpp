#pragma once

#include "reflection_config.hpp"
#include <clang/AST/ASTConsumer.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/ArgumentsAdjusters.h>
#include <clang/Tooling/Tooling.h>

class ReflFrontendAction : public clang::ASTFrontendAction {
  protected:
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
        clang::CompilerInstance& CI,
        llvm::StringRef) override;

    ReflectionCLI cli;

  public:
    ReflFrontendAction(ReflectionCLI const& cli) : cli{cli} {}
};

class ReflFrontendActionFactory
    : public clang::tooling::FrontendActionFactory {
  public:
    explicit ReflFrontendActionFactory(ReflectionCLI const& cli)
        : cli{cli} {}

    std::unique_ptr<clang::FrontendAction> create() override;

  private:
    ReflectionCLI cli;
};

void run_binary_symbols_collection(ReflectionCLI const& cli);
void run_semantic_symbols_collection(ReflectionCLI const& cli);

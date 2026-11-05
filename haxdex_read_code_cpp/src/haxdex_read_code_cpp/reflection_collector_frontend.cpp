#include "reflection_collector_frontend.hpp"
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/JSONCompilationDatabase.h>
#include <haxdex_read_code_cpp_common/reflection_config.hpp>
#include <hstd_cpp_lib/logger/logger.hpp>

#include "haxdex_read_code_cpp_common/demangle_json.hpp"
#include "reflection_collector.hpp"


std::unique_ptr<clang::ASTConsumer> ReflFrontendAction::CreateASTConsumer(
    clang::CompilerInstance& CI,
    llvm::StringRef) {
    HSLOG_TRACE("Ast consumer verbose: {}", cli.verbose_log);
    auto consumer = std::make_unique<ReflASTConsumer>(CI, cli);
    if (cli.mode == ReflectionCLI::Mode::AllMainSymbolsInCompilationDb) {
        consumer->Visitor.visitMode = ReflASTVisitor::VisitMode::AllMainTranslationUnit;
    } else if (cli.mode == ReflectionCLI::Mode::AllAnotatedSymbols) {
        consumer->Visitor.visitMode = ReflASTVisitor::VisitMode::AllAnnotated;
    } else {
        consumer->Visitor.visitMode = ReflASTVisitor::VisitMode::AllTargeted;
    }

    HSLOG_INFO("Create AST consumer with visit mode {}", consumer->Visitor.visitMode);

    return consumer;
}

void run_semantic_symbols_collection(ReflectionCLI const& cli) {
    std::string ErrorMessage;
    auto        JSONDB = clang::tooling::JSONCompilationDatabase::loadFromFile(
        cli.reflection.compilation_database,
        ErrorMessage,
        clang::tooling::JSONCommandLineSyntax::AutoDetect);

    if (JSONDB) {
        HSLOG_TRACE("Using compilation database {}", cli.reflection.compilation_database);
    } else {
        throw hstd::runtime_error::init(
            fmt::format(
                "Failed to process provided JSON DB, failure was: {}\n"
                "CompilationDB = {}",
                ErrorMessage,
                cli.reflection.compilation_database));
    }

    clang::tooling::ArgumentsAdjustingCompilations adjustedCompilations(
        std::move(JSONDB));

    adjustedCompilations.appendArgumentsAdjuster(
        [cli](
            clang::tooling::CommandLineArguments const& Args,
            llvm::StringRef Filename) -> clang::tooling::CommandLineArguments {
            return dropReflectionPlugin(Args, Filename, cli);
        });

    clang::tooling::ClangTool tool(adjustedCompilations, cli.input);

    if (cli.reflection.toolchain_include) {
        if (!hstd::fs::is_directory(
                std::string(cli.reflection.toolchain_include.value()))) {
            throw hstd::FilesystemError::init(
                fmt::format(
                    "Toolchain include is not a directory or does not "
                    "exist "
                    "'{}'",
                    cli.reflection.toolchain_include.value()));
        }
    }

    if (cli.verbose_log) {
        HSLOG_TRACE("Using toolchain include {}", cli.reflection.toolchain_include);
        HSLOG_TRACE("Configuration parse OK, running tool");
    }

    HSLOG_INFO("Starting reflection frontend tool run");

    int result = tool.run(std::make_unique<ReflFrontendActionFactory>(cli).get());

    if (result != 0) { throw std::runtime_error("Reflection tool execution failed"); }
}

std::unique_ptr<clang::FrontendAction> ReflFrontendActionFactory::create() {
    HSLOG_TRACE("Refl frontend action factory create");
    return std::make_unique<ReflFrontendAction>(cli);
}

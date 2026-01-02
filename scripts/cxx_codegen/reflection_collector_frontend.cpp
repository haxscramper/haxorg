#include "reflection_collector_frontend.hpp"
#include "reflection_config.hpp"
#include <hstd/ext/logger.hpp>
#include <clang/Tooling/JSONCompilationDatabase.h>
#include <clang/Tooling/CommonOptionsParser.h>

#include "reflection_collector.hpp"

namespace {
std::string getClangResourceDir() {
    std::array<char, 256> buffer;
    std::string           result;

    // Ask clang itself where its resource directory is
    std::unique_ptr<FILE, decltype(&pclose)> pipe(
        popen("clang -print-resource-dir 2>/dev/null", "r"), pclose);

    if (pipe) {
        while (fgets(buffer.data(), buffer.size(), pipe.get())
               != nullptr) {
            result += buffer.data();
        }
        // Remove trailing newline
        if (!result.empty() && result.back() == '\n') {
            result.pop_back();
        }
    }

    return result;
}
} // namespace

std::unique_ptr<clang::ASTConsumer> ReflFrontendAction::CreateASTConsumer(
    clang::CompilerInstance& CI,
    llvm::StringRef) {
    HSLOG_ERROR("Ast consumer verbose: {}", cli.verbose_log);
    auto consumer = std::make_unique<ReflASTConsumer>(CI, cli);
    if (cli.mode == ReflectionCLI::Mode::AllMainSymbolsInCompilationDb) {
        consumer->Visitor.visitMode = ReflASTVisitor::VisitMode::
            AllMainTranslationUnit;
    } else if (cli.mode == ReflectionCLI::Mode::AllAnotatedSymbols) {
        consumer->Visitor.visitMode = ReflASTVisitor::VisitMode::
            AllAnnotated;
    } else {
        consumer->Visitor.visitMode = ReflASTVisitor::VisitMode::
            AllTargeted;
    }

    return consumer;
}

/// Filter out compilation options that were used in the compilation
/// database -- remove reflection plugin usage, precompiled headers, and
/// add provided toolchain include configuration.
clang::tooling::CommandLineArguments dropReflectionPLugin(
    const clang::tooling::CommandLineArguments& Args,
    llvm::StringRef                             Filename,
    ReflectionCLI const&                        cli) {
    clang::tooling::CommandLineArguments filteredArgs;

    auto push = [&](std::string const& value,
                    int                line = __builtin_LINE()) {
        if (cli.verbose_log) { HSLOG_TRACE("+++ Adding {}", value); }
        filteredArgs.push_back(value);
    };

    bool has_resource_dir = false;
    for (size_t i = 0; i < Args.size(); ++i) {
        auto drop = [&](int line = __builtin_LINE()) {
            if (cli.verbose_log) {
                HSLOG_TRACE("!!! Discarding {}", Args[i]);
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
        } else if (Args[i].find("-resource-dir") != std::string::npos) {
            has_resource_dir = true;
            push(Args[i]);
        } else {
            push(Args[i]);
        }
    }

    if (!has_resource_dir) {
        std::string resourceDir = getClangResourceDir();
        if (!resourceDir.empty()) {
            push("-resource-dir");
            push(resourceDir);
        }
    }

    // TODO Redirect warnings and other diagnostics into a temporary
    // location Use serif output.
    push("-Wno-everything");
    if (cli.verbose_log) { push("-v"); }
    if (cli.reflection.toolchain_include) {
        push("-isystem");
        push(cli.reflection.toolchain_include.value());
    }
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
    if (cli.reflection.no_std_include) { push("-nostdinc++"); }
    // NOTE: The comment above was relevant when the custom standard
    // library was used in the build process. When the system-provided one
    // is used it does not seem to be required (on the contrary, removing
    // std include causes issues with `cstdddef`), but the message above
    // should stay there regardless.

    if (cli.verbose_log) {
        HSLOG_TRACE("Filtered command line arguments");
        for (auto const& arg : filteredArgs) {
            HSLOG_TRACE("[ ] {}", arg);
        }

        HSLOG_TRACE(":: ");
        for (auto const& arg : filteredArgs) { HSLOG_TRACE(" {}", arg); }
        HSLOG_TRACE("");
    }

    return filteredArgs;
}

void run_semantic_symbols_collection(const ReflectionCLI& cli) {
    std::string ErrorMessage;
    auto JSONDB = clang::tooling::JSONCompilationDatabase::loadFromFile(
        cli.reflection.compilation_database,
        ErrorMessage,
        clang::tooling::JSONCommandLineSyntax::AutoDetect);

    if (JSONDB) {
        HSLOG_TRACE(
            "Using compilation database {}",
            cli.reflection.compilation_database);
    } else {
        throw hstd::runtime_error::init(
            std::format(
                "Failed to process provided JSON DB, failure was: {}\n"
                "CompilationDB = {}",
                ErrorMessage,
                cli.reflection.compilation_database));
    }

    clang::tooling::ArgumentsAdjustingCompilations adjustedCompilations(
        std::move(JSONDB));

    adjustedCompilations.appendArgumentsAdjuster(
        [cli](
            const clang::tooling::CommandLineArguments& Args,
            llvm::StringRef                             Filename)
            -> clang::tooling::CommandLineArguments {
            return dropReflectionPLugin(Args, Filename, cli);
        });

    clang::tooling::ClangTool tool(adjustedCompilations, cli.input);

    if (!cli.reflection.toolchain_include) {
        if (!hstd::fs::is_directory(
                std::string(cli.reflection.toolchain_include.value()))) {
            throw hstd::FilesystemError::init(
                std::format(
                    "Toolchain include is not a directory or does not "
                    "exist "
                    "'{}'",
                    cli.reflection.toolchain_include.value()));
        }
    }

    if (cli.verbose_log) {
        HSLOG_TRACE(
            "Using toolchain include {}",
            cli.reflection.toolchain_include);
        HSLOG_TRACE("Configuration parse OK, running tool");
    }

    int result = tool.run(
        std::make_unique<ReflFrontendActionFactory>(cli).get());

    if (result != 0) {
        throw std::runtime_error("Reflection tool execution failed");
    }
}

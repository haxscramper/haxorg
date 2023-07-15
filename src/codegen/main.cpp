#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <clang/Basic/Builtins.h>

#include <fmt/core.h>
#include <fmt/ranges.h>

#include "gen_description.hpp"
#include "gen_converter.hpp"

using namespace clang;
using namespace clang::tooling;
using namespace llvm;


QTextStream qcout;

int main(int argc, const char** argv) {
    cl::OptionCategory category("codegen");
    cl::opt<Str>       OutputDirectory(
        "output",
        cl::desc("Specify output directory"),
        cl::value_desc("filename"),
        cl::cat(category));

    auto cli = CommonOptionsParser::create(argc, argv, category);

    if (!cli) {
        llvm::errs() << cli.takeError();
        return 1;
    }

    CommonOptionsParser& OptionsParser = cli.get();

    YAML::Node doc = YAML::LoadFile(
        OptionsParser.getSourcePathList().at(0));
    GenDescription description = doc.as<GenDescription>();

    ASTBuilder         builder;
    clang::LangOptions LOpts;


    clang::DiagnosticsEngine Diag(
        new clang::DiagnosticIDs(), new clang::DiagnosticOptions());
    clang::FileSystemOptions FileSystemOpts;
    clang::FileManager       FileMgr{FileSystemOpts};
    clang::SourceManager     SM{Diag, FileMgr};
    clang::IdentifierTable   idents;
    clang::SelectorTable     sels;
    clang::Builtin::Context  builtins;
    TranslationUnitKind      TUKind;

    clang::ASTContext context(LOpts, SM, idents, sels, builtins, TUKind);
    builder.setContext(&context);
    clang::TranslationUnitDecl* tu        = convert(builder, description);
    std::string                 formatted = ASTBuilder::clangToString(tu);
    std::cout << formatted << std::endl;
}

#pragma once
#include <optional>

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/FrontendPluginRegistry.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/ASTConsumers.h>
#include <clang/Sema/Sema.h>
#include <unordered_set>

// Auto-generated protobuf definition, provided by cmake run
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/JsonUse.hpp>
#include "reflection_defs.pb.h"
#include <hstd/system/reflection.hpp>
#include <hstd/system/macros.hpp>

#define REFL_NAME "refl"

/// `[[refl]]` attribute provider
struct ExampleAttrInfo : public clang::ParsedAttrInfo {
    ExampleAttrInfo() {
        static constexpr Spelling spellings[]{
            /// __attribute__((REFL_NAME))
            {clang::ParsedAttr::AS_GNU, REFL_NAME},
            /// [[REFL_NAME]]
            {clang::ParsedAttr::AS_CXX11, REFL_NAME},
        };
        Spellings = spellings;

        // Allow 0 or 1 arguments
        OptArgs = 1;
        NumArgs = 0;
    }
    AttrHandling handleDeclAttribute(
        clang::Sema&             S,
        clang::Decl*             D,
        const clang::ParsedAttr& Attr) const override;
};


/// Data extraction AST visitor, collects annotated types into the protobuf
/// definitions that can later be imported by the python scripts.
class ReflASTVisitor : public clang::RecursiveASTVisitor<ReflASTVisitor> {
  public:
    TU*  out;
    bool verbose = false;

    void log_visit(
        clang::Decl const* Decl,
        std::string const& msg      = "",
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION());


    explicit ReflASTVisitor(
        clang::ASTContext* Context,
        TU*                tu,
        bool               verbose)
        : Ctx(Context), out(tu), verbose(verbose) {}


    std::optional<std::string> get_refl_params(clang::Decl const* decl);


    using DiagKind = clang::DiagnosticsEngine::Level;

    /// Helper wrapper for clang diagnostic printer
    template <unsigned N>
    clang::DiagnosticBuilder Diag(
        clang::DiagnosticsEngine::Level L,
        const char (&FormatString)[N],
        std::optional<clang::SourceLocation> const& Loc = std::nullopt,
        int         line                                = __builtin_LINE(),
        char const* function = __builtin_FUNCTION()) {
        std::string message = std::format(
            "from code {}:{}", function, line);
        auto& D = Ctx->getDiagnostics();
        if (Loc) {
            return D.Report(*Loc, D.getCustomDiagID(L, FormatString))
                << message;
        } else {
            return D.Report(D.getCustomDiagID(L, FormatString)) << message;
        }
    }

    /// Print qualified clang type as string
    std::string dump(clang::QualType const& Typ) {
        std::string              typeName;
        llvm::raw_string_ostream rso(typeName);
        Typ.dump(rso, *Ctx);
        rso.flush();
        return typeName;
    }


    std::string dump(clang::Decl const* Decl, int head = -1);

    /// Fill in information about namespaces used in elaborated type
    std::vector<QualType> getNamespaces(
        clang::ElaboratedType const*                elab,
        std::optional<clang::SourceLocation> const& Loc);

    std::vector<QualType> getNamespaces(
        clang::QualType const&                      In,
        std::optional<clang::SourceLocation> const& Loc);

    std::vector<QualType> getNamespaces(
        clang::NamespaceDecl const*                 Namespace,
        std::optional<clang::SourceLocation> const& Loc);

    std::vector<QualType> getNamespaces(
        clang::Decl*                                Decl,
        std::optional<clang::SourceLocation> const& Loc);

    void applyNamespaces(
        QualType*                    Out,
        std::vector<QualType> const& Namespaces,
        int                          line     = __builtin_LINE(),
        char const*                  function = __builtin_FUNCTION());

    void fillTypeTemplates(
        QualType*                                   Out,
        clang::QualType const&                      In,
        std::optional<clang::SourceLocation> const& Loc);

    void fillTypeRec(
        QualType*                                   Out,
        clang::QualType const&                      In,
        std::optional<clang::SourceLocation> const& Loc);

    /// This function 'fills' the type in both directions (adding parent
    /// namespaces to the 'left' and parameters to the 'right') around the
    /// type name as needed. Target output type will be assigned with
    /// information from the 'base' of the \arg In.
    void fillType(
        QualType*                                   Out,
        clang::QualType const&                      In,
        std::optional<clang::SourceLocation> const& Loc);

    void fillTypeRec(
        QualType*                                   Out,
        clang::TemplateArgument const&              Arg,
        std::optional<clang::SourceLocation> const& Loc);

    /// Convert expression into a simplified protobuf description --
    /// mapping whole set of C++ complexities here is likely not possible
    /// anyway, so simplified approximation will suffice.
    void fillExpr(
        Expr*                                       Out,
        clang::Expr const*                          In,
        std::optional<clang::SourceLocation> const& Loc);

    void fillFieldDecl(Record::Field* sub, const clang::FieldDecl* field);

    void fillParmVarDecl(Arg* arg, clang::ParmVarDecl const* parm);

    void fillMethodDecl(
        Record::Method*             sub,
        const clang::CXXMethodDecl* method);
    void fillRecordDecl(Record* rec, clang::RecordDecl* Decl);
    void fillCxxRecordDecl(Record* rec, const clang::CXXRecordDecl* Decl);
    void fillSharedRecordData(Record* rec, const clang::RecordDecl* Decl);


    bool VisitCXXRecordDecl(clang::CXXRecordDecl* Declaration);
    bool VisitFunctionDecl(clang::FunctionDecl* Decl);
    bool VisitEnumDecl(clang::EnumDecl* Decl);
    bool VisitTypedefDecl(clang::TypedefDecl* Decl);
    bool VisitRecordDecl(clang::RecordDecl* Decl);
    bool IndirectFieldDecl(clang::IndirectFieldDecl* Decl);


    bool isDescribedEnum(const clang::EnumDecl* enumDecl);
    bool isDescribedRecord(const clang::RecordDecl* recordDecl);

    bool                       isRefl(const clang::Decl* Decl);
    std::optional<std::string> getDoc(const clang::Decl* Decl);

    bool shouldVisit(const clang::Decl* Decl);

    /// List of absolute paths for files whose declarations must be added
    /// to the information about the translation units.
    std::unordered_set<std::string> targetFiles;
    /// What group of declarations must be handled by the visitor
    enum class VisitMode
    {
        /// All elements that are explicitly annotated with `[[refl]]`
        /// attribute, irreespective of the declaration file.
        AllAnnotated,
        /// All declarations contained in explicitly allowed target files.
        AllTargeted,
        /// All declarations if they were placed in the main file of the
        /// translation unit.
        AllMainTranslationUnit,
    };

    VisitMode visitMode = VisitMode::AllAnnotated;

  private:
    clang::ASTContext* Ctx;
};

struct IncludeCollectorCallback : public clang::PPCallbacks {
    clang::SourceManager* sourceManager;
    TU*                   out;

    IncludeCollectorCallback(TU* tu, clang::SourceManager* sourceManager)
        : out(tu), sourceManager(sourceManager) {}

    void InclusionDirective(
        clang::SourceLocation             HashLoc,
        clang::Token const&               IncludeTok,
        llvm::StringRef                   FileName,
        bool                              IsAngled,
        clang::CharSourceRange            FilenameRange,
        clang::OptionalFileEntryRef       File,
        llvm::StringRef                   SearchPath,
        llvm::StringRef                   RelativePath,
        clang::Module const*              Imported,
        clang::SrcMgr::CharacteristicKind FileType) override;
};


class ReflASTConsumer : public clang::ASTConsumer {
  public:
    std::unique_ptr<TU>      out;
    ReflASTVisitor           Visitor;
    clang::CompilerInstance& CI;

    std::optional<std::string> outputPathOverride;
    explicit ReflASTConsumer(clang::CompilerInstance& CI, bool verbose);

    virtual void HandleTranslationUnit(clang::ASTContext& Context);
};

struct BinarySymbolInfo {
    std::string name;
    std::string demangled;
    json        demangled_parse;
    uint64_t    size;
    uint64_t    address;
    DESC_FIELDS(
        BinarySymbolInfo,
        (name, demangled, demangled_parse, size, address));
};

struct BinarySectionInfo {
    std::string                   name;
    std::vector<BinarySymbolInfo> symbols;
    DESC_FIELDS(BinarySectionInfo, (name, symbols));
};

struct BinaryFileInfo {
    std::vector<BinarySectionInfo> sections;
    DESC_FIELDS(BinaryFileInfo, (sections));
};

BinaryFileInfo getSymbolsInBinary(const std::string& path);
std::string    parseBinarySymbolName(std::string const& name);

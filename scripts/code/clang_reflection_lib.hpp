#pragma once

#include <iostream>
#include <fstream>
#include <optional>

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/FrontendPluginRegistry.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/ASTConsumers.h>
#include <clang/Sema/Sema.h>

// Auto-generated protobuf definition, provided by cmake run
#include "reflection_defs.pb.h"

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
    TU* out;
    explicit ReflASTVisitor(clang::ASTContext* Context, TU* tu)
        : Ctx(Context), out(tu) {}

    using DiagKind = clang::DiagnosticsEngine::Level;


    /// Helper wrapper for clang diagnostic printer
    template <unsigned N>
    clang::DiagnosticBuilder Diag(
        clang::DiagnosticsEngine::Level L,
        const char (&FormatString)[N],
        std::optional<clang::SourceLocation> const& Loc = std::nullopt) {
        auto& D = Ctx->getDiagnostics();
        if (Loc) {
            return D.Report(*Loc, D.getCustomDiagID(L, FormatString));
        } else {
            return D.Report(D.getCustomDiagID(L, FormatString));
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

    /// Fill in information about namespaces used in elaborated type
    void fillNamespaces(
        /// Update information on this outgoing type
        QualType*                                   Out,
        clang::ElaboratedType const*                elab,
        std::optional<clang::SourceLocation> const& Loc);

    /// This function 'fills' the type in both directions (adding parent
    /// namespaces to the 'left' and parameters to the 'right') around the
    /// type name as needed. Target output type will be assigned with
    /// information from the 'base' of the \arg In.
    void fillType(
        QualType*                                   Out,
        clang::QualType const&                      In,
        std::optional<clang::SourceLocation> const& Loc);

    void fillType(
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

    void fillFieldDecl(Record::Field* sub, clang::FieldDecl* field);

    void fillParmVarDecl(Arg* arg, clang::ParmVarDecl const* parm);

    void fillMethodDecl(Record::Method* sub, clang::CXXMethodDecl* method);


    bool VisitCXXRecordDecl(clang::CXXRecordDecl* Declaration);
    bool isRefl(clang::Decl* Decl);
    std::optional<std::string> getDoc(const clang::Decl* Decl);

  private:
    clang::ASTContext* Ctx;
};

class ReflASTConsumer : public clang::ASTConsumer {
  public:
    std::unique_ptr<TU>      out;
    ReflASTVisitor           Visitor;
    clang::CompilerInstance& CI;

    std::optional<std::string> outputPathOverride;
    explicit ReflASTConsumer(clang::CompilerInstance& CI)
        : out(std::make_unique<TU>())
        , Visitor(&CI.getASTContext(), out.get())
        , CI(CI) {}

    virtual void HandleTranslationUnit(clang::ASTContext& Context);
};

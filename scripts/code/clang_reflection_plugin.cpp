#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/FrontendPluginRegistry.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/ASTConsumers.h>
#include <clang/Sema/Sema.h>
#include <iostream>
#include <fstream>
#include <optional>

#include "reflection_defs.pb.h"

#define REFL_NAME "refl"


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
        const clang::ParsedAttr& Attr) const override {
        clang::AnnotateAttr* created = clang::AnnotateAttr::Create(
            S.Context,
            Attr.getAttrName()->deuglifiedName(),
            nullptr,
            0,
            Attr.getRange());
        D->addAttr(created);
        return AttributeApplied;
    }
};


static clang::ParsedAttrInfoRegistry::Add<ExampleAttrInfo> Z(
    REFL_NAME,
    "example attribute description");

class ReflASTVisitor : public clang::RecursiveASTVisitor<ReflASTVisitor> {
  public:
    TU* out;
    explicit ReflASTVisitor(clang::ASTContext* Context, TU* tu)
        : Ctx(Context), out(tu) {}

    using DiagKind = clang::DiagnosticsEngine::Level;


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

    std::string dump(clang::QualType const& Typ) {
        std::string              typeName;
        llvm::raw_string_ostream rso(typeName);
        Typ.dump(rso, *Ctx);
        rso.flush();
        return typeName;
    }

    void fillNamespaces(
        QualType*                                   Out,
        clang::ElaboratedType const*                elab,
        std::optional<clang::SourceLocation> const& Loc) {
        if (const clang::NestedNameSpecifier* nns = elab->getQualifier()) {
            // Iterate through the Nested Name Specifier
            llvm::SmallVector<clang::NestedNameSpecifier const*> spaces;
            while (nns) {
                spaces.push_back(nns);
                nns = nns->getPrefix();
            }

            std::reverse(spaces.begin(), spaces.end());
            for (auto const* nns : spaces) {
                clang::NestedNameSpecifier::SpecifierKind kind = nns->getKind();
                QualType* Space = Out->add_spaces();
                switch (kind) {
                    case clang::NestedNameSpecifier::Identifier: {
                        Space->set_name(nns->getAsIdentifier()->getName());
                        break;
                    }

                    case clang::NestedNameSpecifier::Namespace: {
                        Space->set_name(
                            nns->getAsNamespace()->getNameAsString());
                        break;
                    }

                    case clang::NestedNameSpecifier::NamespaceAlias: {
                        Diag(
                            DiagKind::Warning,
                            "TODO Implement namespace alias expansion",
                            Loc);
                        Space->set_name(
                            nns->getAsNamespaceAlias()->getNameAsString());
                        break;
                    }
                }
            }
        }
    }

    /// This function 'fills' the type in both directions (adding parent
    /// namespaces to the 'left' and parameters to the 'right') around the
    /// type name as needed. Target output type will be assigned with
    /// information from the 'base' of the \arg In.
    void fillType(
        QualType*                                   Out,
        clang::QualType const&                      In,
        std::optional<clang::SourceLocation> const& Loc) {
        Out->set_isconst(In.isConstQualified());
        Out->set_isref(In->isReferenceType());
        if (In->isReferenceType()) {
            fillType(Out, In->getPointeeType(), Loc);
        } else if (In->isBuiltinType()) {
            Out->set_name(In.getAsString());
        } else if (
            clang::ElaboratedType const* elab = In->getAs<
                                                clang::ElaboratedType>()) {
            fillNamespaces(Out, elab, Loc);
            fillType(Out, elab->getNamedType(), Loc);
        } else if (In->isRecordType()) {
            Out->set_name(
                In->getAs<clang::RecordType>()->getTypeClassName());
        } else {
            Diag(
                DiagKind::Warning,
                "Unhandled serialization for a type %0 (%1)",
                Loc)
                << In << dump(In);
        }
    }

    void fillExpr(
        Expr*                                       Out,
        clang::Expr const*                          In,
        std::optional<clang::SourceLocation> const& Loc) {
        if (auto val = In->getIntegerConstantExpr(*Ctx)) {
            Out->set_kind(ExprKind::Lit);
            llvm::SmallString<32> Str;
            val->toString(Str);
            Out->set_value(Str.str().str());
        } else {
            Diag(DiagKind::Warning, "Unhandled expression filled.", Loc);
        }
    }

    void fillFieldDecl(Record::Field* sub, clang::FieldDecl* field) {
        sub->set_name(field->getNameAsString());
        fillType(
            sub->mutable_type(), field->getType(), field->getLocation());
    }

    void fillParmVarDecl(Arg* arg, clang::ParmVarDecl const* parm) {
        arg->set_name(parm->getNameAsString());
        fillType(
            arg->mutable_type(), parm->getType(), parm->getLocation());
        if (parm->hasDefaultArg()) {
            fillExpr(
                arg->mutable_default_(),
                parm->getDefaultArg(),
                parm->getLocation());
        }
    }

    void fillMethodDecl(
        Record::Method*       sub,
        clang::CXXMethodDecl* method) {
        sub->set_name(method->getNameAsString());
        fillType(
            sub->mutable_returnty(),
            method->getReturnType(),
            method->getLocation());

        for (clang::ParmVarDecl const* parm : method->parameters()) {
            fillParmVarDecl(sub->add_args(), parm);
        }
    }


    bool VisitCXXRecordDecl(clang::CXXRecordDecl* Declaration) {
        for (clang::AnnotateAttr* Attr :
             Declaration->specific_attrs<clang::AnnotateAttr>()) {

            if (Attr->getAnnotation() == REFL_NAME) {
                Record* rec = out->add_records();
                rec->set_name(Declaration->getNameAsString());

                for (clang::FieldDecl* field : Declaration->fields()) {
                    fillFieldDecl(rec->add_fields(), field);
                }

                for (clang::CXXMethodDecl* method :
                     Declaration->methods()) {
                    fillMethodDecl(rec->add_methods(), method);
                }
            }
        }

        return true;
    }

  private:
    clang::ASTContext* Ctx;
};

class ReflASTConsumer : public clang::ASTConsumer {
  public:
    std::unique_ptr<TU>      out;
    ReflASTVisitor           Visitor;
    clang::CompilerInstance& CI;
    explicit ReflASTConsumer(clang::CompilerInstance& CI)
        : out(std::make_unique<TU>())
        , Visitor(&CI.getASTContext(), out.get())
        , CI(CI) {}

    virtual void HandleTranslationUnit(clang::ASTContext& Context) {
        Visitor.TraverseDecl(Context.getTranslationUnitDecl());
        clang::DiagnosticsEngine& Diags = CI.getDiagnostics();
        std::string   path = CI.getFrontendOpts().OutputFile + ".pb";
        std::ofstream file{
            path, std::ios::out | std::ios::trunc | std::ios::binary};

        if (file.is_open()) {
            out->SerializePartialToOstream(&file);
            file.close();
            Diags.Report(Diags.getCustomDiagID(
                clang::DiagnosticsEngine::Remark,
                "Wrote compiler reflection to file: "
                "'%0'"))
                << path;
        } else {
            Diags.Report(Diags.getCustomDiagID(
                clang::DiagnosticsEngine::Warning,
                "Could not write compiler reflection data from a file: "
                "'%0'"))
                << path;
        }
    }
};

class ReflPluginAction : public clang::PluginASTAction {
  protected:
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
        clang::CompilerInstance& CI,
        llvm::StringRef) override {

        return std::make_unique<ReflASTConsumer>(CI);
    }

    bool ParseArgs(
        const clang::CompilerInstance&  CI,
        const std::vector<std::string>& args) override {
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

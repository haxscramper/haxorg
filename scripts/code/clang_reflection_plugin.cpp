#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/FrontendPluginRegistry.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/ASTConsumers.h>
#include <clang/Sema/Sema.h>
#include <iostream>
#include <fstream>

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

    bool VisitCXXRecordDecl(clang::CXXRecordDecl* Declaration) {
        for (clang::AnnotateAttr* Attr :
             Declaration->specific_attrs<clang::AnnotateAttr>()) {

            if (Attr->getAnnotation() == REFL_NAME) {

                Record* rec = out->add_records();
                rec->set_name(Declaration->getNameAsString());
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

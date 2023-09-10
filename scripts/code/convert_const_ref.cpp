#include <iostream>
#include <string>
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "llvm/Support/CommandLine.h"

using namespace clang;
using namespace clang::tooling;
using namespace llvm;

class MyASTVisitor : public RecursiveASTVisitor<MyASTVisitor> {
  public:
    explicit MyASTVisitor(Rewriter& R) : TheRewriter(R) {}

    bool VisitParmVarDecl(ParmVarDecl* Param) {
        auto Type = Param->getType();
        if (Type->isLValueReferenceType()) {
            auto PointeeType = Type->getPointeeType();
            if (PointeeType.isConstQualified()) {
                auto        InnerType  = PointeeType.getUnqualifiedType();
                std::string NewTypeStr = "CR<" + InnerType.getAsString()
                                       + ">";
                TheRewriter.ReplaceText(
                    Param->getSourceRange(), NewTypeStr);
            }
        }
        return true;
    }

  private:
    Rewriter& TheRewriter;
};

class MyASTConsumer : public ASTConsumer {
  public:
    MyASTConsumer(Rewriter& R) : Visitor(R) {}

    void HandleTranslationUnit(ASTContext& Context) override {
        Visitor.TraverseDecl(Context.getTranslationUnitDecl());
    }

  private:
    MyASTVisitor Visitor;
};

class MyFrontendAction : public clang::ASTFrontendAction {
  public:
    MyFrontendAction() {}

    void EndSourceFileAction() override {
        TheRewriter
            .getEditBuffer(TheRewriter.getSourceMgr().getMainFileID())
            .write(llvm::outs());
    }

    virtual std::unique_ptr<ASTConsumer> CreateASTConsumer(
        clang::CompilerInstance& CI,
        llvm::StringRef          file) override {
        TheRewriter.setSourceMgr(CI.getSourceManager(), CI.getLangOpts());
        return std::make_unique<MyASTConsumer>(TheRewriter);
    }

  private:
    Rewriter TheRewriter;
};

// Custom Factory
class MyFrontendActionFactory
    : public clang::tooling::FrontendActionFactory {
  public:
    std::unique_ptr<clang::FrontendAction> create() override {
        return std::unique_ptr<clang::FrontendAction>(
            new MyFrontendAction());
    }
};


static llvm::cl::OptionCategory ToolingSampleCategory(
    "Refactor T const& to CR<T>");

int main(int argc, const char** argv) {
    auto cli = CommonOptionsParser::create(
        argc, argv, ToolingSampleCategory);

    if (!cli) {
        llvm::errs() << cli.takeError();
        return 1;
    }

    CommonOptionsParser& OptionsParser = cli.get();


    ClangTool Tool(
        OptionsParser.getCompilations(),
        OptionsParser.getSourcePathList());

    MyFrontendActionFactory Factory;
    return Tool.run(&Factory);
}

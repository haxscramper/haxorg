#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/FrontendPluginRegistry.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Sema/Sema.h>
#include <iostream>

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
        std::cout << "Created annotated attribute with spelling '"
                  << created->getAnnotation().str() << "'" << std::endl;
        D->addAttr(created);
        // Handle the attribute
        return AttributeApplied;
    }
};


static clang::ParsedAttrInfoRegistry::Add<ExampleAttrInfo> Z(
    REFL_NAME,
    "example attribute description");

class ReflASTVisitor : public clang::RecursiveASTVisitor<ReflASTVisitor> {
  public:
    explicit ReflASTVisitor(clang::ASTContext* Context) : Ctx(Context) {
        std::cout << "Registering AST visitor" << std::endl;
    }

    bool VisitCXXRecordDecl(clang::CXXRecordDecl* Declaration) {
        std::cout << "Visiting CXXRecordDecl declaration '"
                  << Declaration->getNameAsString() << "'"
                  << " with " << Declaration->getAttrs().size()
                  << " attributes" << std::endl;

        for (clang::AnnotateAttr* Attr :
             Declaration->specific_attrs<clang::AnnotateAttr>()) {
            std::cout << "Found record declaration with attribute '"
                      << Attr->getAnnotation().str() << "'" << std::endl;

            if (Attr->getAnnotation() == REFL_NAME) {

                clang::QualType returnType = Ctx->VoidTy; // specify the
                                                          // return type
                clang::FunctionDecl* newMethod = clang::FunctionDecl::
                    Create(
                        /*ASTContext=*/*Ctx,
                        /*DeclContext=*/Declaration,
                        /*Location=*/clang::SourceLocation(),
                        /*StartLoc=*/clang::SourceLocation(),
                        /*Name=*/
                        clang::DeclarationName(
                            &Ctx->Idents.get("call_me")),
                        /*Type=*/returnType,
                        /*TypeSourceInfo=*/nullptr,
                        /*StorageClass=*/clang::SC_None);
                Declaration->addDecl(newMethod);
                std::cout << "Added declaration to the output"
                          << std::endl;
            }
        }
        return true;
    }

  private:
    clang::ASTContext* Ctx;
};

class ReflASTConsumer : public clang::ASTConsumer {
  public:
    explicit ReflASTConsumer(clang::ASTContext* Context)
        : Visitor(Context) {}

    virtual void HandleTranslationUnit(clang::ASTContext& Context) {
        Visitor.TraverseDecl(Context.getTranslationUnitDecl());
    }

  private:
    ReflASTVisitor Visitor;
};

class ReflPluginAction : public clang::PluginASTAction {
  protected:
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
        clang::CompilerInstance& CI,
        llvm::StringRef) override {
        std::cout << "Requested creation of the REFL AST plugin"
                  << std::endl;
        return std::make_unique<ReflASTConsumer>(&CI.getASTContext());
    }

    bool ParseArgs(
        const clang::CompilerInstance&  CI,
        const std::vector<std::string>& args) override {
        std::cout << "Requested argument parse" << std::endl;
        return true;
    }

  public:
    ReflPluginAction() {
        std::cout << "Created refl plugin action" << std::endl;
    }
};

static clang::FrontendPluginRegistry::Add<ReflPluginAction> X(
    "refl-plugin",
    "Reflection plugin");

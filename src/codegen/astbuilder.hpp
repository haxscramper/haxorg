#pragma once

#include <clang/ASTMatchers/Dynamic/Parser.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>


#include <hstd/stdlib/Vec.hpp>

using namespace clang;

/// Class to manage state required for the AST creation - `ASTContext`,
/// identifiers. Constructs AST nodes with no extra location information.
/// Class declares collection of constructor methods and structures - one
/// for each clang node kind. Structures allow using named parameters via
/// designated initializers (`.Cond = <expr>`)
class ASTBuilder {
    ASTContext*     context;
    IdentifierTable idents;

    /// Create empty source location
    clang::SourceLocation sl() { return clang::SourceLocation(); }
    /// Get reference to stored context
    ASTContext& ctx() { return *context; }
    /// Get translation unit declaration
    DeclContext* dc() { return context->getTranslationUnitDecl(); }
    /// Create new identifier info from \arg name
    IdentifierInfo* id(const std::string& name) {
        return &idents.get(name);
    }
    /// Create declaration namme from \arg name
    DeclarationName name(const std::string& name) {
        return DeclarationName(id(name));
    }

  public:
    /// Update stored AST context
    void setContext(ASTContext* _context) { context = _context; }

    struct ParmVarDeclParams {
        QualType     type;
        std::string  name;
        StorageClass storage = SC_None;
        Expr*        defArg  = nullptr;
        ParmVarDeclParams() {}
        ParmVarDeclParams(ParmVarDecl* decl)
            : type(decl->getOriginalType())
            , name(decl->getNameAsString())
            , storage(decl->getStorageClass())
            , defArg(decl->getDefaultArg()) {}
    };


    ParmVarDecl* ParmVarDecl(const ParmVarDeclParams& p);

    void setParams(FunctionDecl& decl, Vec<ParmVarDeclParams>& params) {
        Vec<class ParmVarDecl*> out;
        for (const auto& param : params) {
            out.push_back(ParmVarDecl(param));
        }

        decl.setParams(out);
    }


    /// Function declaration signature
    struct FunctionDeclParams {
        std::string   Name;
        QualType      ResultTy = QualType();
        Vec<QualType> ArgsTy   = {};
        StorageClass  Storage  = SC_None;
        Stmt*         Body     = nullptr;
        bool          Inline   = false;
    };


    /// Create function declaration. If \arg params is not empty use it to
    /// construct argument types in the resulting function signature.
    FunctionDecl* FunctionDecl(
        FunctionDeclParams            p,
        const Vec<ParmVarDeclParams>& params = {});

    struct TypeDeclParams {
        std::string            name;
        CXXRecordDecl::TagKind tagKind = CXXRecordDecl::TagKind::
            TTK_Struct;
    };

    CXXRecordDecl* CXXRecordDecl(TypeDeclParams const& params);

    struct CompoundStmtParams {
        ArrayRef<Stmt*> Stmts;
    };

    CompoundStmt* CompoundStmt(const CompoundStmtParams& p) {
        return CompoundStmt::Create(
            ctx(), p.Stmts, clang::FPOptionsOverride{}, sl(), sl());
    }

    struct VarDeclParams {
        std::string  Name;
        QualType     Type;
        StorageClass Storage = SC_None;
        Expr*        Init    = nullptr;
    };

    VarDecl* VarDecl(VarDeclParams p);

    struct IfStmtParams {
        Expr*      Cond;
        Vec<Stmt*> Then;
        Vec<Stmt*> Else;

        Expr*           Init = nullptr;
        class VarDecl*  Var  = nullptr;
        IfStatementKind kind = IfStatementKind::Ordinary;
    };

    IfStmt* IfStmt(const IfStmtParams& p);

    class IfStmt* IfStmt(const ArrayRef<IfStmtParams>& p);

    DeclStmt* Stmt(Decl* decl) {
        return new (ctx()) DeclStmt(DeclGroupRef(decl), sl(), sl());
    }

    struct BinaryOperatorParams {
        BinaryOperator::Opcode opc;
        Expr*                  lhs;
        Expr*                  rhs;
        ExprValueKind          VK;
        ExprObjectKind         OK;
        FPOptionsOverride      FPFeatures;
    };

    class BinaryOperator* BinaryOperator(const BinaryOperatorParams& p);

    class BinaryOperator* XCall(
        const BinaryOperator::Opcode& opc,
        Vec<Expr*>                    args) {
        return BinaryOperator(
            {.opc = opc, .lhs = args[0], .rhs = args[1]});
    }

    struct UnaryOperatorParams {
        UnaryOperator::Opcode opc;
        Expr*                 Expr;
        ExprValueKind         VK;
        ExprObjectKind        OK;
        FPOptionsOverride     FPFeatures;
    };

    class UnaryOperator* UnaryOperator(const UnaryOperatorParams& p);

    class UnaryOperator* XCall(
        const UnaryOperator::Opcode opc,
        Expr*                       expr) {
        return UnaryOperator({.opc = opc, .Expr = expr});
    }

    DeclRefExpr* Ref(class VarDecl* decl);
    DeclRefExpr* Ref(const std::string& name) {
        auto tmp = VarDecl({name, QualType()});
        return Ref(tmp);
    }

    DeclRefExpr* Ref(const clang::FunctionDecl* decl) {
        return Ref(decl->getName().str());
    }

    struct CallExprParams {
        Expr*      Fn;
        Vec<Expr*> Args = {};
    };

    clang::CallExpr* CallExpr(const CallExprParams& p) {
        return CallExpr::Create(
            ctx(),
            p.Fn,
            p.Args,
            QualType(),
            ExprValueKind(),
            sl(),
            FPOptionsOverride());
    }

    clang::CallExpr* XCall(const std::string& name, Vec<Expr*> Args = {}) {
        return CallExpr({Ref(name), Args});
    }

    clang::CallExpr* XCall(
        const class FunctionDecl* decl,
        Vec<Expr*>                Args = {}) {
        return CallExpr({Ref(decl), Args});
    }

    IntegerLiteral* Literal(uint64_t value) {
        return IntegerLiteral::Create(
            ctx(),
            llvm::APInt(sizeof(value) * 8, value),
            ctx().IntTy,
            sl());
    }

    clang::StringLiteral* Literal(const std::string& str) {
        return clang::StringLiteral::Create(
            ctx(),
            str,
            clang::StringLiteral::StringKind::Ordinary,
            false,
            QualType(),
            sl());
    }

    CXXThrowExpr* Throw(Expr* expr) {
        return new (ctx())
            CXXThrowExpr(expr, expr->getType(), sl(), false);
    }

    ReturnStmt* Return(Expr* expr) {
        return ReturnStmt::Create(ctx(), sl(), expr, nullptr);
    }

    class Expr* Expr(Expr* expr) { return expr; }

    clang::TranslationUnitDecl* TranslationUnit(Vec<clang::Decl*> decls) {
        auto tu = clang::TranslationUnitDecl::Create(*context);
        for (auto const& decl : decls) {
            tu->addDecl(decl);
        }
        return tu;
    }

    template <typename T>
    static std::string clangToString(
        T*                    t,
        PrintingPolicy const& policy = clang::PrintingPolicy(
            clang::LangOptions())) {
        std::string              out_str;
        llvm::raw_string_ostream outstream(out_str);
        t->print(outstream, policy);
        return out_str;
    }

    static std::string clangToString(
        QualType const&       t,
        PrintingPolicy const& policy = clang::PrintingPolicy(
            clang::LangOptions())) {
        std::string              out_str;
        llvm::raw_string_ostream outstream(out_str);
        t.print(outstream, policy);
        return out_str;
    }
};

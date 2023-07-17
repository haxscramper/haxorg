#pragma once

#include <hstd/wrappers/textlayouter.hpp>
#include <hstd/system/macros.hpp>

#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Str.hpp>

/// Class to manage state required for the AST creation - `ASTContext`,
/// identifiers. Constructs AST nodes with no extra location information.
/// Class declares collection of constructor methods and structures - one
/// for each clang node kind. Structures allow using named parameters via
/// designated initializers (`.Cond = <expr>`)
class ASTBuilder {
  public:
    using Res    = layout::Block::Ptr;
    using b      = layout::Block;
    using LytStr = layout::LytStr;
    layout::SimpleStringStore store;
    Res string(QString const& str) { return b::text(store.str(str)); }

    struct Ident {
        Vec<Str> spaces;
    };

    struct Doc {
        Str brief;
        Str full;
    };

    struct QualType {
        Ident ident;
        bool  isConst;
    };

    enum class StorageClass
    {
        None,
        Static
    };


    struct ParmVarDeclParams {
        QualType     type;
        Str          name;
        StorageClass storage = StorageClass::None;
        Str          defArg  = "";
    };


    Res ParmVarDecl(const ParmVarDeclParams& p);

    /// Function declaration signature
    struct FunctionDeclParams {
        Str                    Name;
        QualType               ResultTy = QualType();
        Vec<ParmVarDeclParams> Args     = {};
        StorageClass           Storage  = StorageClass::None;
        Res                    Body     = nullptr;
        bool                   Inline   = false;
    };


    /// Create function declaration. If \arg params is not empty use it to
    /// construct argument types in the resulting function signature.
    Res FunctionDecl(FunctionDeclParams const& p);

    QualType Type(Str const&);
    Res      Type(QualType const& type);

    enum class AccessSpecifier
    {
        Public,
        Private,
        Protected
    };

    struct RecordDeclParams {
        struct Method {
            FunctionDeclParams params;
            Doc                doc;
            bool               isStatic;
            bool               isConst;
            bool               isVirtual;
            AccessSpecifier    access = AccessSpecifier::Public;
        };

        struct Field {
            ParmVarDeclParams params;
            Doc               doc;
            bool              isStatic = false;
            AccessSpecifier   access   = AccessSpecifier::Public;
        };

        struct Member {
            SUB_VARIANTS(Kind, Data, data, getKind, Method, Field);
            Member(CR<Data> data) : data(data) {}
            Data data;
        };

        Str         name;
        Doc         doc;
        Vec<Str>    bases;
        Vec<Member> members;
    };

    Res FieldDecl(RecordDeclParams::Field const& field);
    Res MethodDecl(RecordDeclParams::Method const& method);
    Res RecordDecl(RecordDeclParams const& params);

    struct CompoundStmtParams {
        Vec<Res> Stmts;
    };

    Res brace(Vec<Res> const& elements) {
        return b::stack({
            string("{"),
            b::stack(elements),
            string("}"),
        });
    }

    Res csv(CVec<Res> items, bool isLine = true, bool isTrailing = false) {
        return b::join(items, string(","), isLine, isTrailing);
    }

    Res CompoundStmt(const CompoundStmtParams& p) {
        return brace(p.Stmts);
    }

    Res VarDecl(ParmVarDeclParams const& p);

    struct IfStmtParams {
        Res      Cond;
        Res      Then;
        Opt<Res> Else;

        Res      Init = nullptr;
        Opt<Res> Var;
    };

    Res IfStmt(const IfStmtParams& p);
    Res IfStmt(const Vec<IfStmtParams>& p);
    Res IfStmt(const Span<IfStmtParams>& p);

    Res XCall(Str const& opc, Vec<Res> args);
    Res XStmt(Str const& opc, Res arg) {
        return b::line({string(opc), string(" "), arg, string(";")});
    }

    Res Literal(uint64_t value) { return string(QString::number(value)); }
    Res Literal(const Str& str) { return string("\"" + str + "\""); }

    Res Throw(Res expr) { return XStmt("throw", expr); }
    Res Return(Res expr) { return XStmt("return", expr); }
    Res Continue(Res expr) { return XStmt("continue", expr); }
    Res TranslationUnit(Vec<Res> stmts) { return b::stack(stmts); }
};

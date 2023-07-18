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
        Ident() {}
        Ident(Str const& name) : spaces({name}) {}
        Ident(Vec<Str> const& name) : spaces(name) {}
    };

    struct DocParams {
        Str brief;
        Str full;
    };

    struct QualType {
        Ident ident;
        bool  isConst = false;
        bool  isPtr   = false;
        bool  isRef   = false;

        QualType() {}
        QualType(Str const& name) { ident = Ident(name); }

        QualType& Ref(bool set = true) {
            isRef = set;
            return *this;
        }

        QualType& Ptr(bool set = true) {
            isPtr = set;
            return *this;
        }

        QualType& Const(bool set = true) {
            isConst = set;
            return *this;
        }
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

    Res Doc(DocParams const& doc);
    Res ParmVarDecl(const ParmVarDeclParams& p);

    /// Function declaration signature
    struct FunctionDeclParams {
        // TODO make into ident
        Str                    Name;
        DocParams              doc;
        QualType               ResultTy = QualType("void");
        Vec<ParmVarDeclParams> Args     = {};
        StorageClass           Storage  = StorageClass::None;
        Opt<Vec<Res>>          Body     = std::nullopt;
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
            bool               isStatic;
            bool               isConst;
            bool               isVirtual;
            AccessSpecifier    access = AccessSpecifier::Public;
        };

        struct Field {
            ParmVarDeclParams params;
            DocParams         doc;
            bool              isStatic = false;
            AccessSpecifier   access   = AccessSpecifier::Public;
        };

        struct Member {
            SUB_VARIANTS(Kind, Data, data, getKind, Method, Field);
            Member(CR<Data> data) : data(data) {}
            Data data;
        };

        Str         name;
        DocParams   doc;
        Vec<Str>    bases;
        Vec<Member> members;
    };

    Res FieldDecl(RecordDeclParams::Field const& field);
    Res MethodDecl(RecordDeclParams::Method const& method);
    Res RecordDecl(RecordDeclParams const& params);

    struct MacroDeclParams {
        struct Param {
            Str  name;
            bool isEllipsis;
        };
        DocParams  doc;
        Vec<Param> params;
        Str        name;
        Vec<Str>   definition;
    };

    Res MacroDecl(MacroDeclParams const& params);

    struct EnumDeclParams {
        struct Field {
            DocParams doc;
            Str       name;
            Opt<Str>  value;
        };

        Str        name;
        Str        base;
        DocParams  doc;
        bool       isEnumClass = true;
        Vec<Field> fields;
    };

    Res EnumDecl(EnumDeclParams const& params);

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

    Res pars(Res const& arg) {
        return b::line({string("("), arg, string(")")});
    }

    Res block(
        Res const&      head,
        Vec<Res> const& content,
        bool            trailingLine = false) {

        auto result = b::stack({
            b::line({head, string(" {")}),
            b::indent(2, b::stack(content)),
            string("}"),
        });

        if (trailingLine) {
            result->add(string(""));
        }

        return result;
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

    struct CaseStmtParams {
        Res      Expr;
        Vec<Res> Body;
        bool     Compound  = true;
        bool     Autobreak = true;
        bool     OneLine   = false;
    };

    struct SwitchStmtParams {
        Res                 Expr;
        Vec<CaseStmtParams> Cases;
    };

    Res CaseStmt(CaseStmtParams const& params);
    Res SwitchStmt(SwitchStmtParams const& params);

    Res XCall(Str const& opc, Vec<Res> args);
    Res XStmt(Str const& opc, Res arg) {
        return b::line({string(opc), string(" "), arg, string(";")});
    }

    Res XStmt(Str const& opc) {
        return b::line({string(opc), string(";")});
    }

    Res Literal(uint64_t value) { return string(QString::number(value)); }
    Res Literal(const Str& str) { return string("\"" + str + "\""); }

    Res Throw(Res expr) { return XStmt("throw", expr); }
    Res Return(Res expr) { return XStmt("return", expr); }
    Res Continue(Res expr) { return XStmt("continue", expr); }
    Res TranslationUnit(Vec<Res> stmts) { return b::stack(stmts); }
    Res Include(Str file, bool isSystem) {
        return b::line({
            string("#include "),
            string(isSystem ? "<" + file + ">" : "\"" + file + "\""),
        });
    }
};

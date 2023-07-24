#pragma once

#include <hstd/wrappers/textlayouter.hpp>
#include <hstd/system/macros.hpp>

#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/algorithms.hpp>

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


    struct DocParams {
        Str brief;
        Str full;
    };

    Res WithDoc(Res const& content, DocParams const& doc);

    struct QualType {
        Str           name;
        bool          isConst    = false;
        bool          isPtr      = false;
        bool          isRef      = false;
        Vec<QualType> Parameters = {};

        QualType() {}
        QualType(Str const& name) : name(name) {}
        QualType(Str const& name, Vec<QualType> const& Parameters)
            : name(name), Parameters(Parameters) {}

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

    struct IdentParams {
        Vec<QualType> spaces;
        IdentParams() {}
        IdentParams(Str const& name) : spaces({QualType(name)}) {}
        IdentParams(Vec<Str> const& name) {
            for (auto const& n : name) {
                spaces.push_back(QualType(n));
            }
        }
    };

    struct TemplateParamParams {
        struct Param {
            bool       Placeholder = false;
            bool       Variadic    = false;
            Str        Name;
            Vec<Param> Nested;
            Opt<Str>   Concept;
        };

        struct Spec {
            Vec<Param> Params;
        };

        Vec<Spec> Stacks;
    };

    Res Template(TemplateParamParams::Param const& Param);
    Res Template(TemplateParamParams::Spec const& Spec);
    Res Template(TemplateParamParams const& Templ);
    Res WithTemplate(TemplateParamParams const& Templ, Res const& Body);
    Res Ident(IdentParams const& Id);

    enum class StorageClass
    {
        None,
        Static
    };

    struct ParmVarDeclParams {
        QualType     type;
        Str          name;
        bool         isConst = false;
        StorageClass storage = StorageClass::None;
        Opt<Str>     defArg  = std::nullopt;
    };

    Res Doc(DocParams const& doc);
    Res ParmVarDecl(const ParmVarDeclParams& p);

    /// Function declaration signature
    struct FunctionDeclParams {
        // TODO make into ident
        Str                    Name;
        DocParams              doc;
        TemplateParamParams    Template;
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


    struct EnumDeclParams {
        struct Field {
            DocParams doc;
            Str       name;
            Opt<Str>  value;
        };

        Str        name;
        Opt<Str>   base;
        DocParams  doc;
        bool       isEnumClass = true;
        Vec<Field> fields;
    };

    Res EnumDecl(EnumDeclParams const& params);


    enum class AccessSpecifier
    {
        Unspecified,
        Public,
        Private,
        Protected
    };

    Res WithAccess(Res const& content, AccessSpecifier spec);

    struct RecordDeclParams {
        struct Method {
            FunctionDeclParams params;
            bool               isStatic      = false;
            bool               isConst       = false;
            bool               isVirtual     = false;
            bool               isPureVirtual = false;
            AccessSpecifier    access = AccessSpecifier::Unspecified;
        };

        struct Field {
            ParmVarDeclParams params;
            DocParams         doc;
            bool              isStatic = false;
            AccessSpecifier   access   = AccessSpecifier::Unspecified;
        };

        struct Member {
            SUB_VARIANTS(Kind, Data, data, getKind, Method, Field);
            Member(CR<Data> data) : data(data) {}
            Data data;
        };

        using Nested = Variant<
            EnumDeclParams,
            SPtr<RecordDeclParams>,
            Res>;

        Str       name;
        DocParams doc;
        // TODO specify base visibility
        Vec<Str>    bases;
        Vec<Member> members;
        Vec<Nested> nested;
    };

    Res FieldDecl(RecordDeclParams::Field const& field);
    Res MethodDecl(RecordDeclParams::Method const& method);
    Res RecordDecl(RecordDeclParams const& params);

    struct UsingDeclParams {
        Str      newName;
        QualType baseType;
    };

    Res UsingDecl(UsingDeclParams const& params);

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
        bool            trailingLine = false);

    Res csv(CVec<Str> items, bool isLine = true, bool isTrailing = false);

    Res csv(CVec<Res> items, bool isLine = true, bool isTrailing = false) {
        return b::join(items, string(", "), isLine, isTrailing);
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

    Res XCall(
        Str const& opc,
        Vec<Res>   args,
        bool       Stmt = false,
        bool       Line = true);

    Res XStmt(Str const& opc, Res arg) {
        return b::line({string(opc), string(" "), arg, string(";")});
    }

    Res XStmt(Str const& opc) {
        return b::line({string(opc), string(";")});
    }

    Res Trail(
        Res const& first,
        Res const& second,
        Str const& space = " ") {
        return b::line({first, string(space), second});
    }

    Res Comment(
        Vec<Str> const& text,
        bool            Inline = true,
        bool            Doc    = false);

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

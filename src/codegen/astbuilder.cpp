#include "astbuilder.hpp"

ASTBuilder::Res ASTBuilder::ParmVarDecl(const ParmVarDeclParams& p) {}


ASTBuilder::Res ASTBuilder::FunctionDecl(FunctionDeclParams const& p) {}

ASTBuilder::QualType ASTBuilder::Type(Str const& type) {
    return QualType{.ident = Ident{.spaces = {type}}};
}

ASTBuilder::Res ASTBuilder::Type(const QualType& type) {
    return string(type.ident.spaces.at(0));
}


ASTBuilder::Res ASTBuilder::FieldDecl(
    const RecordDeclParams::Field& field) {
    return b::stack({
        field.access == AccessSpecifier::Public ? string("public:")
                                                : string("private:"),
        b::indent(2, VarDecl(field.params)),
    });
}

ASTBuilder::Res ASTBuilder::MethodDecl(
    const RecordDeclParams::Method& method) {}

ASTBuilder::Res ASTBuilder::RecordDecl(const RecordDeclParams& params) {
    Vec<Res> content;

    for (auto const& m : params.members) {
        if (m.getKind() == RecordDeclParams::Member::Kind::Field) {
            content.push_back(FieldDecl(m.getField()));
        } else {
        }
    }

    Res bases = string("");

    return b::stack({
        b::line({
            string("struct "),
            string(params.name),
            bases,
            string(" {"),
        }),
        b::indent(2, b::stack(content)),
        string("};"),
    });
}

ASTBuilder::Res ASTBuilder::VarDecl(ParmVarDeclParams const& p) {
    return b::line({
        Type(p.type),
        string(" "),
        string(p.name),
        p.defArg.empty() ? string("")
                         : b::line({
                             string(" = "),
                             string(p.defArg),
                         }),
        string(";"),
    });
}

ASTBuilder::Res ASTBuilder::IfStmt(const IfStmtParams& p) {
    return b::stack({
        b::line({string("if ("), string(")")}),
        b::indent(2, p.Then),
        b::line({
            p.Else ? b::line({string(" else "), p.Else.value()})
                   : string(""),
        }),
    });
}

ASTBuilder::Res ASTBuilder::IfStmt(const Span<IfStmtParams>& p) {
    if (p.size() == 1) {
        return IfStmt(p[0]);
    } else {
        auto p0 = p[0];

        Span<IfStmtParams> sub = p[slice(1, 1_B)];
        p0.Else                = {IfStmt(sub)};
        return IfStmt(p0);
    }
}

ASTBuilder::Res ASTBuilder::IfStmt(const Vec<IfStmtParams>& p) {
    return IfStmt(p[slice(0, 1_B)]);
}

ASTBuilder::Res ASTBuilder::XCall(const Str& opc, Vec<Res> args) {
    if (opc[0].isLetter()) {
        return b::line({string(opc), string("("), csv(args), string(")")});
    } else {
        if (args.size() == 1) {
            return b::line({string(opc), args.at(0)});
        } else if (args.size() == 2) {
            return b::line({args.at(0), string(opc), args.at(1)});
        } else {
            qFatal(
                "Unexpected number of arguments for operator-like "
                "function call. Expected 1 or 2 but got different amount");
        }
    }
}

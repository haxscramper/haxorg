#include "astbuilder.hpp"

#include <ranges>

namespace rv = std::ranges::views;
namespace rs = std::ranges;

ASTBuilder::Res ASTBuilder::Doc(const DocParams& doc) {
    Vec<Str> content;
    bool     isFirst = true;
    for (auto const& line : doc.brief.split("\n")) {
        if (line.size() == 0) {
            continue;
        } else if (isFirst) {
            content.push_back("\\brief " + line);
            isFirst = false;
        } else {
            content.push_back(line);
        }
    }

    if (!content.empty()) {
        content.push_back("");
    }

    for (auto const& line : doc.full.split("\n")) {
        content.push_back(line);
    }

    while (!content.empty() && content.back().empty()) {
        content.pop_back();
    }

    auto result = b::stack();
    for (auto const& line : content) {
        result->add(string("/// " + line));
    }
    return result;
}

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
        Doc(field.doc),
        b::indent(2, VarDecl(field.params)),
    });
}

ASTBuilder::Res ASTBuilder::MethodDecl(
    const RecordDeclParams::Method& method) {
    return b::stack({
        method.access == AccessSpecifier::Public ? string("public:")
                                                 : string("private:"),
        b::indent(
            2,
            b::stack({
                Doc(method.params.doc),
                b::line({
                    string(method.isStatic ? "static " : ""),
                    string(method.isVirtual ? "virtual " : ""),
                    Type(method.params.ResultTy),
                    string(" "),
                    string(method.params.Name),
                    string("("),
                    string(")"),
                    string(method.isConst ? " const" : ""),
                    string(method.isVirtual ? " = 0" : ""),
                    string(";"),
                }),
            })),
    });
}

ASTBuilder::Res ASTBuilder::RecordDecl(const RecordDeclParams& params) {
    Vec<Res> content;

    for (auto const& m : params.members) {
        if (m.getKind() == RecordDeclParams::Member::Kind::Field) {
            content.push_back(FieldDecl(m.getField()));
        } else if (m.getKind() == RecordDeclParams::Member::Kind::Method) {
            content.push_back(MethodDecl(m.getMethod()));
        }
    }

    Res bases = string("");
    if (!params.bases.empty()) {
        Vec<Res> classes;
        for (auto const& base : params.bases) {
            classes.push_back(string("public " + base));
        }
        bases = b::line({string(" : "), b::join(classes, string(", "))});
    }

    return b::stack({
        Doc(params.doc),
        b::line({
            string("struct "),
            string(params.name),
            bases,
            string(" {"),
        }),
        b::indent(2, b::stack(content)),
        string("};"),
        string(""),
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

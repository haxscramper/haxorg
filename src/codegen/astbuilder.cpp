#include "astbuilder.hpp"

#include <hstd/stdlib/algorithms.hpp>
#include <ranges>

namespace rv = std::ranges::views;
namespace rs = std::ranges;

ASTBuilder::Res ASTBuilder::WithDoc(
    const Res&       content,
    const DocParams& doc) {
    if (doc.brief.empty() && doc.full.empty()) {
        return content;
    } else {
        return b::stack({Doc(doc), content});
    }
}

ASTBuilder::Res ASTBuilder::Template(
    const TemplateParamParams::Param& Param) {
    return b::line({
        Param.Concept
            ? string(*Param.Concept)
            : string(Param.Nested.empty() ? "typename" : "template"),
        string(Param.Placeholder ? "" : " "),
        string(Param.Placeholder ? "" : Param.Name),
        b::surround_non_empty(
            b::map_join(
                Param.Nested,
                [&](TemplateParamParams::Param const& Sub) -> Res {
                    return Template(Sub);
                },
                string(", ")),
            string("<"),
            string(">")),
    });
}

ASTBuilder::Res ASTBuilder::Template(
    const TemplateParamParams::Spec& Spec) {
    return b::line({
        string("template <"),
        b::map_join(
            Spec.Params,
            [&](TemplateParamParams::Param const& Param) {
                return Template(Param);
            },
            string(", ")),
        string(">"),
    });
}

ASTBuilder::Res ASTBuilder::Template(const TemplateParamParams& Templ) {
    return b::map_join(
        Templ.Stacks,
        [&](TemplateParamParams::Spec const& Spec) {
            return Template(Spec);
        },
        b::empty(),
        /* isLine */ false);
}

ASTBuilder::Res ASTBuilder::WithTemplate(
    const TemplateParamParams& Templ,
    const Res&                 Body) {
    if (Templ.Stacks.empty()) {
        return Body;
    } else {
        return b::stack({Template(Templ), Body});
    }
}

ASTBuilder::Res ASTBuilder::Ident(const IdentParams& Id) {
    return b::join(
        map(Id.spaces, [&](QualType const& T) { return Type(T); }),
        string("::"));
}

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

ASTBuilder::Res ASTBuilder::ParmVarDecl(const ParmVarDeclParams& p) {
    return b::line({
        Type(p.type),
        string(" "),
        string(p.name),
        p.defArg ? string(" = " + *p.defArg) : string(""),
    });
}

ASTBuilder::Res ASTBuilder::FunctionDecl(FunctionDeclParams const& p) {
    Vec<Res> Args;
    for (auto const& Arg : p.Args) {
        Args.push_back(ParmVarDecl(Arg));
    }

    auto head = b::line({
        Type(p.ResultTy),
        string(" "),
        string(p.Name),
        pars({b::join(Args, string(", "))}),
    });

    return WithTemplate(
        p.Template,
        p.Body ? block(head, *p.Body, true)
               : b::line({head, string(";")}));
}

ASTBuilder::QualType ASTBuilder::Type(Str const& type) {
    return QualType(type);
}

ASTBuilder::Res ASTBuilder::Type(const QualType& type) {
    return b::line({
        string(type.name),
        type.Parameters.empty()
            ? string("")
            : b::line({
                string("<"),
                b::join(
                    map(type.Parameters,
                        [&](QualType const& in) { return Type(in); }),
                    string(", "),
                    true),
                string(">"),
            }),
        string(
            Str(type.isConst ? " const" : "") + //
            Str(type.isPtr ? "*" : "") +        //
            Str(type.isRef ? "&" : "")          //
            ),
    });
}

ASTBuilder::Res ASTBuilder::WithAccess(
    Res const&                  content,
    ASTBuilder::AccessSpecifier spec) {
    if (spec == AccessSpecifier::Unspecified) {
        return content;
    } else {
        return b::stack({
            (spec == AccessSpecifier::Public
                 ? string("public:")
                 : (spec == AccessSpecifier::Protected
                        ? string("protected:")
                        : string("private:"))),
            b::indent(2, content),
        });
    }
}

ASTBuilder::Res ASTBuilder::FieldDecl(
    const RecordDeclParams::Field& field) {
    return WithAccess(
        WithDoc(
            b::line({
                string(field.isStatic ? "static " : ""),
                VarDecl(field.params),
            }),
            field.doc),
        field.access);
}

ASTBuilder::Res ASTBuilder::MethodDecl(
    const RecordDeclParams::Method& method) {
    auto head = b::line({
        string(method.isStatic ? "static " : ""),
        string(method.isVirtual ? "virtual " : ""),
        Type(method.params.ResultTy),
        string(" "),
        string(method.params.Name),
        string("("),
        b::join(
            map(method.params.Args,
                [&](ASTBuilder::ParmVarDeclParams const& Arg) {
                    return ParmVarDecl(Arg);
                }),
            string(", "),
            true),
        string(")"),
        string(method.isConst ? " const" : ""),
        string(method.isPureVirtual ? " = 0" : ""),
    });


    return WithAccess(
        WithDoc(
            method.params.Body ? block(head, *method.params.Body, true)
                               : b::line({head, string(";")}),
            method.params.doc),
        method.access);
}

ASTBuilder::Res ASTBuilder::RecordDecl(const RecordDeclParams& params) {
    Vec<Res> content;

    for (auto const& m : params.nested) {
        std::visit(
            overloaded{
                [&](EnumDeclParams const& Enum) {
                    content.push_back(EnumDecl(Enum));
                },
                [&](SPtr<RecordDeclParams> const& rec) {
                    content.push_back(RecordDecl(*rec));
                },
                [&](Res const& res) { content.push_back(res); },
            },
            m);
    }

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

ASTBuilder::Res ASTBuilder::UsingDecl(const UsingDeclParams& params) {
    return b::line({
        string("using "),
        string(params.newName),
        string(" = "),
        Type(params.baseType),
        string(";"),
    });
}

ASTBuilder::Res ASTBuilder::MacroDecl(const MacroDeclParams& params) {
    auto definition = b::stack();
    for (auto const& line : params.definition) {
        definition->add(string(line + "  \\"));
    }
    Vec<Res> arguments;
    for (auto const& line : params.params) {
        arguments.push_back(string(line.isEllipsis ? "..." : line.name));
    }

    return b::stack({
        Doc(params.doc),
        b::line({
            string("#define "),
            string(params.name),
            string("("),
            b::join(arguments, string(", ")),
            string(") \\"),
        }),
        b::indent(8, definition),
        string(""),
    });
}

ASTBuilder::Res ASTBuilder::block(
    const Res&      head,
    const Vec<Res>& content,
    bool            trailingLine) {

    auto result = content.size() < 2 ? (b::line({
                      head,
                      string(" { "),
                      b::stack(content),
                      string(" }"),
                  }))
                                     : (b::stack({
                                         b::line({head, string(" {")}),
                                         b::indent(2, b::stack(content)),
                                         string("}"),
                                     }));

    if (trailingLine) {
        if (result->isStack()) {
            result->add(string(""));
        } else {
            result = b::stack({result, string("")});
        }
    }

    return result;
}

ASTBuilder::Res ASTBuilder::csv(
    CVec<Str> items,
    bool      isLine,
    bool      isTrailing) {
    return b::join(
        map(items, [&](Str const& Base) { return string(Base); }),
        string(", "),
        isLine,
        isTrailing);
}

ASTBuilder::Res ASTBuilder::EnumDecl(const EnumDeclParams& params) {
    Q_ASSERT_X(
        0 < params.name.size(),
        "EnumDecl",
        "non-empty enum name required");
    auto fields = b::stack();
    for (auto const& field : params.fields) {
        fields->add(b::stack({
            Doc(field.doc),
            string(field.name + ","), // TODO field value
        }));
    }

    return b::stack({
        Doc(params.doc),
        b::line({
            string("enum "),
            string(params.isEnumClass ? "class " : ""),
            string(params.name + " "),
            string(params.base ? " : " + *params.base : ""),
            string("{"),
        }),
        b::indent(2, fields),
        string("};"),
        string(""),
    });
}

ASTBuilder::Res ASTBuilder::VarDecl(ParmVarDeclParams const& p) {
    return b::line({
        Type(p.type),
        string(" "),
        string(p.isConst ? "const " : ""),
        string(p.name),
        p.defArg ? b::line({string(" = "), string(*p.defArg)})
                 : string(""),
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

ASTBuilder::Res ASTBuilder::CaseStmt(const CaseStmtParams& params) {
    auto     head = b::line({string("case "), params.Expr, string(":")});
    Vec<Res> Body = params.Body
                  + (params.Autobreak ? Vec<Res>{XStmt("break")}
                                      : Vec<Res>{});
    if (params.Compound) {
        return block(head, Body);
    } else {
        if (params.OneLine) {
            return b::line({
                head,
                string(" "),
                b::join(params.Body, string(" ")),
            });
        } else {
            return b::stack({head, b::indent(2, b::stack(Body))});
        }
    }
}

ASTBuilder::Res ASTBuilder::SwitchStmt(const SwitchStmtParams& params) {
    Vec<Res> cases;
    for (auto const& Case : params.Cases) {
        cases.push_back(CaseStmt(Case));
    }

    return block(b::line({string("switch "), pars(params.Expr)}), cases);
}

ASTBuilder::Res ASTBuilder::XCall(
    const Str& opc,
    Vec<Res>   args,
    bool       Stmt,
    bool       Line) {
    if (opc[0].isLetter()) {
        return b::line({
            string(opc),
            string("("),
            csv(args, Line),
            string(Stmt ? ");" : ")"),
        });
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

ASTBuilder::Res ASTBuilder::Comment(
    const Vec<Str>& text,
    bool            Inline,
    bool            Doc) {
    if (Inline) {
        auto content = b::stack();
        for (auto const& line : text) {
            content->add(string(line));
        }

        return b::line(
            {string(Doc ? "/*! " : "/* "), content, string(" */")});

    } else {
        auto result = b::stack();
        for (auto const& line : text) {
            result->add(string((Doc ? "/// " : "// ") + line));
        }
        return result;
    }
}

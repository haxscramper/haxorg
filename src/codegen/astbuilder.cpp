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
        return b.stack({Doc(doc), content});
    }
}

ASTBuilder::Res ASTBuilder::Template(
    const TemplateParams::Typename& Param) {
    return b.line({
        Param.Concept
            ? string(*Param.Concept)
            : string(Param.Nested.empty() ? "typename" : "template"),
        string(Param.Placeholder ? "" : " "),
        string(Param.Placeholder ? "" : Param.Name),
        b.surround_non_empty(
            b.map_join(
                Param.Nested,
                [&](TemplateParams::Typename const& Sub) -> Res {
                    return Template(Sub);
                },
                string(", ")),
            string("<"),
            string(">")),
    });
}

ASTBuilder::Res ASTBuilder::Template(const TemplateParams::Group& Spec) {
    return b.line({
        string("template <"),
        b.map_join(
            Spec.Params,
            [&](TemplateParams::Typename const& Param) {
                return Template(Param);
            },
            string(", ")),
        string(">"),
    });
}

ASTBuilder::Res ASTBuilder::Template(const TemplateParams& Templ) {
    return b.map_join(
        Templ.Stacks,
        [&](TemplateParams::Group const& Spec) { return Template(Spec); },
        b.empty(),
        /* isLine */ false);
}

ASTBuilder::Res ASTBuilder::WithTemplate(
    const TemplateParams& Templ,
    const Res&            Body) {
    if (Templ.Stacks.empty()) {
        return Body;
    } else {
        return b.stack({Template(Templ), Body});
    }
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

    auto result = b.stack();
    for (auto const& line : content) {
        b.at(result).add(string("/// " + line));
    }
    return result;
}

ASTBuilder::Res ASTBuilder::ParmVar(const ParmVarParams& p) {
    return b.line({
        Type(p.type),
        string(" "),
        string(p.name),
        p.defArg ? string(" = " + *p.defArg) : string(""),
    });
}

ASTBuilder::Res ASTBuilder::Function(FunctionParams const& p) {
    auto head = b.line(
        {Type(p.ResultTy), string(" "), string(p.Name), Arguments(p)});

    return WithTemplate(
        p.Template,
        p.Body ? block(head, *p.Body, true) : b.line({head, string(";")}));
}

ASTBuilder::Res ASTBuilder::Arguments(const FunctionParams& p) {
    return b.line({
        string("("),
        b.join(
            map(p.Args,
                [&](ASTBuilder::ParmVarParams const& Arg) {
                    return ParmVar(Arg);
                }),
            string(", "),
            true),
        string(")"),
    });
}

ASTBuilder::Res ASTBuilder::Method(MethodParams const& m) {
    return WithTemplate(
        m.Params.Template,
        b.stack({
            b.line(
                {Type(m.Params.ResultTy),
                 string(" "),
                 Type(m.Class),
                 string("::"),
                 string(m.Params.Name),
                 Arguments(m.Params),
                 m.IsConst ? string(" const {") : string(" {")}),
            b.indent(2, b.stack(*m.Params.Body)),
            string("}"),
        }));
}

ASTBuilder::QualType ASTBuilder::Type(Str const& type) {
    return QualType(type);
}

ASTBuilder::Res ASTBuilder::Type(const QualType& type) {
    return b.line({
        b.join(
            map(type.Spaces,
                [&](QualType const& Space) { return Type(Space); })
                + Vec<Res>{string(type.name)},
            string("::")),
        type.Parameters.empty()
            ? string("")
            : b.line({
                string("<"),
                b.join(
                    map(type.Parameters,
                        [&](QualType const& in) { return Type(in); }),
                    string(", "),
                    !type.verticalParamList),
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
        return b.stack({
            (spec == AccessSpecifier::Public
                 ? string("public:")
                 : (spec == AccessSpecifier::Protected
                        ? string("protected:")
                        : string("private:"))),
            b.indent(2, content),
        });
    }
}

ASTBuilder::Res ASTBuilder::Field(const RecordParams::Field& field) {
    return WithAccess(
        WithDoc(
            b.line({
                string(field.isStatic ? "static " : ""),
                VarDecl(field.params),
            }),
            field.doc),
        field.access);
}

ASTBuilder::Res ASTBuilder::Method(const RecordParams::Method& method) {
    auto head = b.line({
        string(method.isStatic ? "static " : ""),
        string(method.isVirtual ? "virtual " : ""),
        Type(method.params.ResultTy),
        string(" "),
        string(method.params.Name),
        Arguments(method.params),
        string(method.isConst ? " const" : ""),
        string(method.isPureVirtual ? " = 0" : ""),
    });


    return WithAccess(
        WithDoc(
            method.params.Body ? block(head, *method.params.Body, true)
                               : b.line({head, string(";")}),
            method.params.doc),
        method.access);
}

ASTBuilder::Res ASTBuilder::Record(const RecordParams& params) {
    Vec<Res> content;

    for (auto const& m : params.nested) {
        std::visit(
            overloaded{
                [&](EnumParams const& e) { content.push_back(Enum(e)); },
                [&](SPtr<RecordParams> const& rec) {
                    content.push_back(Record(*rec));
                },
                [&](Res const& res) { content.push_back(res); },
            },
            m);
    }

    for (auto const& m : params.members) {
        if (m.getKind() == RecordParams::Member::Kind::Field) {
            content.push_back(Field(m.getField()));
        } else if (m.getKind() == RecordParams::Member::Kind::Method) {
            content.push_back(Method(m.getMethod()));
        }
    }

    Res bases = string("");
    if (!params.bases.empty()) {
        Vec<Res> classes;
        for (auto const& base : params.bases) {
            classes.push_back(b.line({string("public "), Type(base)}));
        }
        bases = b.line({string(" : "), b.join(classes, string(", "))});
    }

    auto head = b.line({
        string("struct "),
        string(params.name),
        b.surround_non_empty(
            b.map_join(
                params.NameParams,
                [&](QualType const& t) { return Type(t); },
                string(", ")),
            string("<"),
            string(">")),
        bases,
        params.IsDefinition ? string(" {") : string(""),
    });

    return WithTemplate(
        params.Template,
        content.empty()
            ? //
            b.stack(
                {Doc(params.doc),
                 b.line(
                     {head,
                      params.IsDefinition ? string("};") : string(";")}),
                 string("")})
            : b.stack(
                {Doc(params.doc),
                 head,
                 b.indent(2, b.stack(content)),
                 params.IsDefinition ? string("};") : string(";"),
                 string("")}));
}

ASTBuilder::Res ASTBuilder::Using(const UsingParams& params) {
    return WithTemplate(
        params.Template,
        b.line({
            string("using "),
            string(params.newName),
            string(" = "),
            Type(params.baseType),
            string(";"),
        }));
}

ASTBuilder::Res ASTBuilder::Macro(const MacroParams& params) {
    auto definition = b.stack();
    for (auto const& line : params.definition) {
        b.at(definition).add(string(line + "  \\"));
    }
    Vec<Res> arguments;
    for (auto const& line : params.params) {
        arguments.push_back(string(line.isEllipsis ? "..." : line.name));
    }

    return b.stack({
        Doc(params.doc),
        b.line({
            string("#define "),
            string(params.name),
            string("("),
            b.join(arguments, string(", ")),
            string(") \\"),
        }),
        b.indent(8, definition),
        string(""),
    });
}

ASTBuilder::Res ASTBuilder::block(
    const Res&      head,
    const Vec<Res>& content,
    bool            trailingLine) {

    auto result = content.size() < 2 //
                    ? b.line(
                        {head,
                         string(" { "),
                         b.stack(content),
                         string(" }")})
                    : b.stack(
                        {b.line({head, string(" {")}),
                         b.indent(2, b.stack(content)),
                         string("}")});

    if (trailingLine) {
        if (b.at(result).isStack()) {
            b.at(result).add(string(""));
        } else {
            result = b.stack({result, string("")});
        }
    }

    return result;
}

ASTBuilder::Res ASTBuilder::csv(
    CVec<Str> items,
    bool      isLine,
    bool      isTrailing) {
    return b.join(
        map(items, [&](Str const& Base) { return string(Base); }),
        string(", "),
        isLine,
        isTrailing);
}

ASTBuilder::Res ASTBuilder::Enum(const EnumParams& params) {
    Q_ASSERT_X(
        0 < params.name.size(),
        "EnumDecl",
        "non-empty enum name required");
    auto fields = b.stack();
    for (auto const& field : params.fields) {
        b.at(fields).add(b.stack({
            Doc(field.doc),
            string(field.name + ","), // TODO field value
        }));
    }

    return b.stack({
        Doc(params.doc),
        b.line({
            string("enum "),
            string(params.isEnumClass ? "class " : ""),
            string(params.name + " "),
            string(params.base ? ": " + *params.base + " " : ""),
            string("{"),
        }),
        b.indent(2, fields),
        string("};"),
        string(""),
    });
}

ASTBuilder::Res ASTBuilder::VarDecl(ParmVarParams const& p) {
    return b.line({
        Type(p.type),
        string(" "),
        string(p.isConst ? "const " : ""),
        string(p.name),
        p.defArg ? b.line({string(" = "), string(*p.defArg)}) : string(""),
        string(";"),
    });
}

ASTBuilder::Res ASTBuilder::IfStmt(const IfStmtParams& p) {
    Res result = b.stack();

    for (int i = 0; i < p.Branches.size(); ++i) {
        bool        first  = i == 0;
        bool        last   = i == p.Branches.high();
        auto const& Branch = p.Branches.at(i);

        Res head = p.LookupIfStructure
                     ? b.line({string(Branch.Cond ? "if" : "")})
                     : b.line({
                         first ? string("if ")
                               : (Branch.Cond ? string("} else if ")
                                              : string("} else ")),
                     });

        if (Branch.Cond) {
            b.at(head).add(string(" ("));
            b.at(head).add(Branch.Cond.value());
            b.at(head).add(string(") "));
        }

        b.at(head).add(string("{"));

        if (p.LookupIfStructure) {
            b.at(head).add(string(" "));
            b.at(head).add(Branch.Then);
            b.at(head).add(string(" }"));
            if (!last) {
                b.at(head).add(string(" else "));
            }
            b.at(result).add(head);
        } else {
            if (Branch.OneLine) {
                b.at(head).add(string(" "));
                b.at(head).add(Branch.Then);
                b.at(result).add(head);
            } else {
                b.at(result).add(head);
                b.at(result).add(b.indent(2, Branch.Then));
            }
        }
    }

    if (!p.LookupIfStructure) {
        b.at(result).add(string("}"));
    }

    return result;
}


ASTBuilder::Res ASTBuilder::CaseStmt(const CaseStmtParams& params) {
    auto head = params.IsDefault
                  ? string("default:")
                  : b.line({string("case "), params.Expr, string(":")});

    Vec<Res> Body = params.Body
                  + (params.Autobreak ? Vec<Res>{XStmt("break")}
                                      : Vec<Res>{});
    if (params.Compound) {
        return block(head, Body);
    } else {
        if (params.OneLine) {
            return b.line({
                head,
                string(" "),
                b.join(params.Body, string(" ")),
            });
        } else {
            return b.stack({head, b.indent(2, b.stack(Body))});
        }
    }
}

ASTBuilder::Res ASTBuilder::SwitchStmt(const SwitchStmtParams& params) {
    Vec<Res> cases;
    for (auto const& Case : params.Cases) {
        cases.push_back(CaseStmt(Case));
    }

    if (params.Default) {
        cases.push_back(CaseStmt(*params.Default));
    }

    return block(b.line({string("switch "), pars(params.Expr)}), cases);
}

ASTBuilder::Res ASTBuilder::XCall(
    const Str& opc,
    Vec<Res>   args,
    bool       Stmt,
    bool       Line) {
    if (opc[0].isLetter()) {
        return b.line({
            string(opc),
            string("("),
            csv(args, Line),
            string(Stmt ? ");" : ")"),
        });
    } else {
        if (args.size() == 1) {
            return b.line({string(opc), args.at(0)});
        } else if (args.size() == 2) {
            return b.line({
                args.at(0),
                string(" "),
                string(opc),
                string(" "),
                args.at(1),
            });
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
        auto content = b.stack();
        for (auto const& line : text) {
            b.at(content).add(string(line));
        }

        return b.line(
            {string(Doc ? "/*! " : "/* "), content, string(" */")});

    } else {
        auto result = b.stack();
        for (auto const& line : text) {
            b.at(result).add(string((Doc ? "/// " : "// ") + line));
        }
        return result;
    }
}

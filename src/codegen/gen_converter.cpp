#include "gen_converter.hpp"
#include <hstd/stdlib/algorithms.hpp>
#include <hstd/stdlib/Debug.hpp>

AB::ParmVarDeclParams toParams(AB& builder, GD::Ident const& ident) {
    AB::ParmVarDeclParams result{};
    result.name   = ident.name;
    result.type   = AB::QualType(ident.type);
    result.defArg = ident.value;
    return result;
}

AB::FunctionDeclParams convert(AB& builder, const GD::Function& func) {
    AB::FunctionDeclParams decl;

    decl.ResultTy = builder.Type(func.result);
    decl.Name     = func.name;
    decl.doc      = convert(builder, func.doc);

    if (func.params) {
        decl.Template.Stacks = {convert(builder, *func.params)};
    }

    if (func.impl) {
        decl.Body = map(func.impl->split("\n"), [&](QString const& str) {
            return builder.string(str);
        });
    }

    for (auto const& parm : func.arguments) {
        decl.Args.push_back(toParams(builder, parm));
    }

    return decl;
}

AB::Res convert(AB& builder, const GD::Ident& ident) {
    return builder.ParmVarDecl(toParams(builder, ident));
}

AB::RecordDeclParams convert(AB& builder, const GD::Struct& record) {
    using RDP = AB::RecordDeclParams;
    RDP params{
        .name  = record.name,
        .doc   = convert(builder, record.doc),
        .bases = record.bases,
    };

    for (auto const& type : record.nested) {
        std::visit(
            overloaded{
                [&](SPtr<GD::Struct> Struct) {
                    auto const& tmp = std::make_shared<
                        AB::RecordDeclParams>(convert(builder, *Struct));
                    params.nested.push_back(tmp);
                },
                [&](SPtr<GD::Enum> Enum) {
                    auto const& [decl, describe] = convert(
                        builder, *Enum, true);
                    params.nested.push_back(decl);
                    params.nested.push_back(describe);
                },
                [&](SPtr<GD::Function> Func) {},
                [&](SPtr<GD::TypeGroup> TypeGroup) {
                    for (auto const& sub : convert(builder, *TypeGroup)) {
                        params.nested.push_back(sub);
                    }
                },
                [&](GD::Include const& Include) {
                    params.nested.push_back(
                        builder.Include(Include.what, Include.isSystem));
                },
                [&](GD::Pass const& Pass) {
                    params.nested.push_back(builder.string(Pass.what));
                },
                [&]() {},
            },
            type);
    }

    for (auto const& member : record.fields) {
        auto mem = RDP::Member{RDP::Field{
            .params = AB::ParmVarDeclParams{
                .type = builder.Type(member.type),
                .name = member.name,
                .isConst = member.isConst,
                .defArg = member.value,
            },
            .doc = AB::DocParams{
                .brief = member.doc.brief,
                .full = member.doc.full,
            },
            .isStatic = member.isStatic,
        }};

        params.members.push_back(mem);
    }

    for (auto const& method : record.methods) {
        params.members.push_back(RDP::Member{AB::RecordDeclParams::Method{
            .params    = convert(builder, method),
            .isStatic  = method.isStatic,
            .isConst   = method.isConst,
            .isVirtual = method.isVirtual,
        }});
    }

    {
        Vec<GenTu::Field>    extraFields;
        Vec<GenTu::Function> extraMethods;
        for (auto const& nested : record.nested) {
            if (std::holds_alternative<SPtr<GenTu::TypeGroup>>(nested)) {
                auto const& group = std::get<SPtr<GenTu::TypeGroup>>(
                    nested);
                if (!group->kindGetter.empty()) {
                    extraMethods.push_back(GenTu::Function{
                        .name    = group->kindGetter,
                        .result  = group->enumName,
                        .isConst = true,
                    });
                }

                if (!group->variantName.empty()) {
                    extraFields.push_back(GenTu::Field{
                        .name = group->variantField,
                    });
                }
            }
        }

        auto fields = map(
            record.fields + extraFields, [&](GenTu::Field const& field) {
                return builder.string(field.name);
            });

        auto methods = map(
            record.methods + extraMethods,
            [&](GenTu::Function const& method) {
                return AB::b::line(Vec<AB::Res>{
                    builder.string("("),
                    builder.string(method.result),
                    builder.pars(builder.csv({
                        map(method.arguments,
                            [&](GenTu::Ident const& ident) {
                                return builder.string(ident.type);
                            }),
                    })),
                    builder.string(method.isConst ? " const" : ""),
                    builder.string(") "),
                    builder.string(method.name),
                });
            });

        params.nested.push_back(builder.XCall(
            "BOOST_DESCRIBE_CLASS",
            {
                builder.string(record.name),
                builder.pars(builder.csv(record.bases, false)),
                builder.pars(builder.string("")),
                builder.pars(builder.string("")),
                builder.pars(builder.csv(
                    fields + methods,
                    (fields.size() < 6 && methods.size() < 2))),
            },
            false,
            (fields.size() < 4 && methods.size() < 1)));
    }

    return params;
}

Pair<ASTBuilder::EnumDeclParams, ASTBuilder::Res> convert(
    ASTBuilder&        builder,
    const GenTu::Enum& entry,
    bool               nested) {
    AB::EnumDeclParams params;

    params.name      = entry.name;
    params.doc.brief = entry.doc.brief;
    params.doc.full  = entry.doc.full;
    params.base      = entry.base;
    for (auto const& field : entry.fields) {
        params.fields.push_back(AB::EnumDeclParams::Field{
            .doc   = {.brief = field.doc.brief, .full = field.doc.full},
            .name  = field.name,
            .value = field.value,
        });
    }

    Vec<AB::Res> arguments = Vec<AB::Res>{builder.string(entry.name)}
                           + map(entry.fields,
                                 [&](GenTu::EnumField const& Field) {
                                     return builder.string(Field.name);
                                 });

    return {
        params,
        builder.XCall(
            nested ? "BOOST_DESCRIBE_NESTED_ENUM" : "BOOST_DESCRIBE_ENUM",
            arguments),
    };
}


Vec<AB::Res> convert(AB& builder, const GD::TypeGroup& record) {
    Vec<AB::Res> decls;
    Vec<Str>     typeNames;
    for (auto const& item : record.types) {
        if (item.concreteKind) {
            typeNames.push_back(item.name);
        }
    }

    if (false && 0 < record.enumName.size()) {
        AB::EnumDeclParams enumDecl;
        for (auto const& item : typeNames) {
            enumDecl.fields.push_back(
                AB::EnumDeclParams::Field{.name = item});
        }

        enumDecl.name = record.enumName;

        Str strName = "_text";
        Str resName = "_result";

        decls.push_back(builder.EnumDecl(enumDecl));
        AB::SwitchStmtParams switchTo{
            .Expr = builder.string(resName),
        };

        for (auto const& field : enumDecl.fields) {
            switchTo.Cases.push_back(AB::CaseStmtParams{
                .Expr = builder.string(enumDecl.name + "::" + field.name),
                .Body = {builder.Return(builder.Literal(field.name))},
                .Compound  = false,
                .Autobreak = false,
                .OneLine   = true,
            });
        }

        AB::FunctionDeclParams fromEnum{
            .Name = "from_enum",
            .ResultTy = AB::QualType("char").Ptr().Const(),
            .Args = {
                AB::ParmVarDeclParams{
                    .type = AB::QualType(record.enumName),
                    .name = resName,
                },
            },
            .Body = Vec<AB::Res>{builder.SwitchStmt(switchTo),},
        };

        decls.push_back(builder.FunctionDecl(fromEnum));
    }


    if (0 < record.iteratorMacroName.size()) {
        AB::MacroDeclParams iteratorMacro;

        for (auto const& item : typeNames) {
            iteratorMacro.definition.push_back("__IMPL(" + item + ")");
        }

        iteratorMacro.params = {{"__IMPL"}};
        iteratorMacro.name   = record.iteratorMacroName;
        decls.push_back(builder.MacroDecl(iteratorMacro));
    }

    for (auto const& sub : record.types) {
        decls.push_back(builder.RecordDecl(convert(builder, sub)));
    }

    if (!record.variantName.empty() && !record.enumName.empty()) {
        Vec<AB::Res> Arguments{
            builder.string(record.enumName),
            builder.string(record.variantName),
            builder.string(record.variantField),
            builder.string(record.kindGetter),
        };

        for (auto const& kind : typeNames) {
            Arguments.push_back(builder.string(kind));
        }

        // Continue using macros for the time being, so this code can be
        // enabled later
        if (false) {
            decls.push_back(builder.UsingDecl(AB::UsingDeclParams{
                .newName  = record.variantName,
                .baseType = AB::QualType(
                    "Variant",
                    map(typeNames,
                        [&](Str const& Type) {
                            return AB::QualType(Type);
                        })),
            }));
        }


        decls.push_back(builder.XCall("SUB_VARIANTS", Arguments, true));
        decls.push_back(builder.FieldDecl(AB::RecordDeclParams::Field{
            .params = AB::ParmVarDeclParams{
                .type   = AB::QualType(record.variantName),
                .name   = record.variantField,
                .defArg = record.variantValue,
            }}));
    }

    return decls;
}


AB::Res convert(AB& builder, const GD& desc) {

    Vec<AB::Res> decls;
    for (auto const& item : desc.entries) {
        decls.append(convert(builder, item));
    }
    return builder.TranslationUnit(decls);
}

AB::DocParams convert(AB& builder, const GenTu::Doc& doc) {
    return AB::DocParams{.brief = doc.brief, .full = doc.full};
}

Vec<ASTBuilder::Res> convert(
    ASTBuilder&         builder,
    const GenTu::Entry& entry) {
    Vec<AB::Res> decls;
    std::visit(
        overloaded{
            [&](SPtr<GD::Struct> item) {
                decls.push_back(
                    builder.RecordDecl(convert(builder, *item)));
            },
            [&](SPtr<GD::TypeGroup> item) {
                decls.append(convert(builder, *item));
            },
            [&](GD::Include const& Include) {
                decls.push_back(
                    builder.Include(Include.what, Include.isSystem));
            },
            [&](SPtr<GD::Enum> const& Enum) {
                auto const& [decl, describe] = convert(
                    builder, *Enum, false);
                decls.push_back(builder.EnumDecl(decl));
                decls.push_back(describe);
            },
            [&](SPtr<GD::Function> const& Func) {
                decls.push_back(
                    builder.FunctionDecl(convert(builder, *Func)));
            },
            [&](GD::Pass const& Pass) {
                decls.push_back(builder.string(Pass.what));
            },
            [](auto const& it) { qFatal("Unexpected kind"); },
        },
        entry);
    return decls;
}

ASTBuilder::TemplateParamParams::Spec convert(
    ASTBuilder&         builder,
    CVec<GenTu::TParam> Params) {
    return ASTBuilder::TemplateParamParams::Spec{
        .Params = map(Params, [&](GenTu::TParam const& Param) {
            return AB::TemplateParamParams::Param{.Name = Param.name};
        })};
}

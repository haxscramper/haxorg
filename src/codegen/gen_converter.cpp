#include "gen_converter.hpp"
#include <hstd/stdlib/algorithms.hpp>
#include <hstd/stdlib/Debug.hpp>

using RDP = AB::RecordParams;

ASTBuilder::TemplateParams::Group GenConverter::convertParams(
    CVec<GenTu::TParam> Params) {
    return ASTBuilder::TemplateParams::Group{
        .Params = map(Params, [&](GenTu::TParam const& Param) {
            return AB::TemplateParams::Typename{.Name = Param.name};
        })};
}


AB::ParmVarParams GenConverter::convertIdent(GD::Ident const& ident) {
    return AB::ParmVarParams{
        .name   = ident.name,
        .type   = AB::QualType(ident.type),
        .defArg = ident.value,
    };
}

GenConverter::Res GenConverter::convert(const GenTu::Function& func) {
    return builder.Function(convertFunction(func));
}

AB::FunctionParams GenConverter::convertFunction(
    const GD::Function& func) {
    AB::FunctionParams decl{
        .ResultTy = builder.Type(func.result),
        .Name     = func.name,
        .doc      = convertDoc(func.doc),
    };

    if (func.params) {
        decl.Template.Stacks = {convertParams(*func.params)};
    }

    if (func.impl) {
        decl.Body = map(func.impl->split("\n"), [&](QString const& str) {
            return builder.string(str);
        });
    }

    for (auto const& parm : func.arguments) {
        decl.Args.push_back(convertIdent(parm));
    }

    return decl;
}


AB::DocParams GenConverter::convertDoc(const GenTu::Doc& doc) {
    return AB::DocParams{.brief = doc.brief, .full = doc.full};
}

AB::Res GenConverter::convert(const GD::Ident& ident) {
    return builder.ParmVar(convertIdent(ident));
}


GenConverter::Res GenConverter::convert(const GenTu::Namespace& space) {
    Res         result = builder.b.stack();
    WithContext tmpCtx(this, AB::QualType(space.name).asNamespace());

    builder.b.add_at(result,
        builder.string("namespace " + space.name + "{"));
    for (auto const& sub : space.entries) {
        builder.b.add_at(result,convert(sub));
        builder.b.add_at(result,std::move(pendingToplevel));
    }

    builder.b.add_at(result,builder.string("}"));

    return result;
}


AB::Res GenConverter::convert(const GD::Struct& record) {

    RDP params{
        .name  = record.name,
        .doc   = convertDoc(record.doc),
        .bases = map(
            record.bases,
            [](Str const& base) { return AB::QualType(base); }),
    };

    WithContext tmpCtx(this, AB::QualType(record.name));

    for (auto const& type : record.nested) {
        for (const auto& sub : convert(type)) {
            params.nested.push_back(sub);
        }
    }

    for (auto const& member : record.fields) {
        auto mem = RDP::Member{RDP::Field{
            .params = AB::ParmVarParams{
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
        params.members.push_back(RDP::Member{RDP::Method{
            .params    = convertFunction(method),
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
                return builder.b.line(Vec<AB::Res>{
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
            /*Line=*/(fields.size() < 4 && methods.size() < 1)));
    }

    return builder.Record(params);
}

GenConverter::Res GenConverter::convert(const GenTu::Enum& entry) {
    auto FromParams = AB::FunctionParams{
        .Name     = "from_string",
        .ResultTy = AB::QualType("Opt", {AB::QualType(entry.name)}),
        .Args     = {AB::ParmVarParams{
                .type = AB::QualType("QString"),
                .name = "value",
        }}};

    auto ToParams = AB::FunctionParams{
        .Name     = "to_string",
        .ResultTy = AB::QualType("QString"),
        .Args     = {AB::ParmVarParams{
                .type = AB::QualType(entry.name),
                .name = "value",
        }}};

    bool isToplevel = true;
    for (auto const& ctx : context) {
        if (!ctx.isNamespace) {
            isToplevel = false;
            break;
        }
    }

    if (isSource) {
        if (isToplevel) {
            auto Class = AB::QualType(
                "enum_serde", {AB::QualType(entry.name)});

            AB::IfStmtParams SwichFrom{.LookupIfStructure = true};
            for (auto const& field : entry.fields) {
                SwichFrom.Branches.push_back(AB::IfStmtParams::Branch{
                    .OneLine = true,
                    .Then    = builder.Return(
                        builder.string(entry.name + "::" + field.name)),
                    .Cond = builder.XCall(
                        "==",
                        {builder.string("value"),
                         builder.Literal(field.name)})});
            }

            SwichFrom.Branches.push_back(AB::IfStmtParams::Branch{
                .OneLine = true,
                .Then = builder.Return(builder.string("std::nullopt"))});

            AB::SwitchStmtParams SwitchTo{
                .Expr    = builder.string("value"),
                .Default = AB::CaseStmtParams{
                  .IsDefault = true,
                  .Compound  = false,
                  .Autobreak = false,
                  .OneLine   = true,
                  .Body      = Vec<AB::Res>{
                    builder.Throw(
                        builder.XCall(
                      "std::domain_error",
                        Vec<AB::Res>{builder.Literal("Unexpected enum value -- cannot be "
                                       "converted to string"),})),
                        },
                    },
                .Cases = map(
                    entry.fields,
                    [&](GenTu::EnumField const& field) -> AB::CaseStmtParams {
                        return AB::CaseStmtParams{
                            .Autobreak = false,
                            .Compound  = false,
                            .OneLine   = true,
                            .Expr      = builder.string(entry.name + "::" + field.name),
                            .Body      = Vec<AB::Res>{builder.Return(
                              builder.Literal(field.name))}};
                    })
            };

            auto FromDefinition = FromParams;
            FromDefinition.Body = Vec<AB::Res>{builder.IfStmt(SwichFrom)},

            pendingToplevel.push_back(builder.Method(
                {.Class = Class, .Params = FromDefinition}));

            auto ToDefininition = ToParams;
            ToDefininition.Body = Vec<AB::Res>{
                builder.SwitchStmt(SwitchTo)};

            pendingToplevel.push_back(builder.Method(
                {.Class = Class, .Params = ToDefininition}));
        }

        return builder.string("");
    } else {

        AB::EnumParams params{
            .name = entry.name,
            .doc  = convertDoc(entry.doc),
            .base = entry.base,
        };

        for (auto const& field : entry.fields) {
            params.fields.push_back(AB::EnumParams::Field{
                .doc  = {.brief = field.doc.brief, .full = field.doc.full},
                .name = field.name,
                .value = field.value,
            });
        }

        if (isToplevel) {
            auto Domain = RDP{
                .name       = "value_domain",
                .Template   = AB::TemplateParams::FinalSpecialization(),
                .NameParams = {AB::QualType(entry.name)},
                .bases      = {AB::QualType(
                              "value_domain_ungapped",
                              {
                                  AB::QualType(entry.name),
                                  AB::QualType(
                                      {entry.name},
                                      entry.fields.front().name),
                                  AB::QualType(
                                      {entry.name},
                                      entry.fields.back().name),
                              })
                                   .withVerticalParams()},
            };

            auto FromDefinition = FromParams;
            auto ToDefininition = ToParams;

            auto Serde = RDP{
                .name       = "enum_serde",
                .Template   = AB::TemplateParams::FinalSpecialization(),
                .NameParams = {AB::QualType(entry.name)}};

            Serde.add(
                RDP::Method{.isStatic = true, .params = FromDefinition});
            Serde.add(
                RDP::Method{.isStatic = true, .params = ToDefininition});

            return builder.b.stack({
                builder.Enum(params),
                builder.Record(Serde),
                builder.Record(Domain),
            });
        } else {
            Vec<AB::Res>
                arguments = Vec<AB::Res>{builder.string(entry.name)}
                          + map(entry.fields,
                                [&](GenTu::EnumField const& Field) {
                                    return builder.string(Field.name);
                                });

            return builder.b.stack({
                builder.Enum(params),
                builder.XCall("BOOST_DESCRIBE_NESTED_ENUM", arguments),
            });
        }
    }
}


Vec<AB::Res> GenConverter::convert(const GD::TypeGroup& record) {
    Vec<AB::Res> decls;
    Vec<Str>     typeNames;
    for (auto const& item : record.types) {
        if (item.concreteKind) {
            typeNames.push_back(item.name);
        }
    }

    if (false && 0 < record.enumName.size()) {
        AB::EnumParams enumDecl;
        for (auto const& item : typeNames) {
            enumDecl.fields.push_back(AB::EnumParams::Field{.name = item});
        }

        enumDecl.name = record.enumName;

        Str strName = "_text";
        Str resName = "_result";

        decls.push_back(builder.Enum(enumDecl));
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

        AB::FunctionParams fromEnum{
            .Name = "from_enum",
            .ResultTy = AB::QualType("char").Ptr().Const(),
            .Args = {
                AB::ParmVarParams{
                    .type = AB::QualType(record.enumName),
                    .name = resName,
                },
            },
            .Body = Vec<AB::Res>{builder.SwitchStmt(switchTo),},
        };

        decls.push_back(builder.Function(fromEnum));
    }


    if (0 < record.iteratorMacroName.size()) {
        AB::MacroParams iteratorMacro;

        for (auto const& item : typeNames) {
            iteratorMacro.definition.push_back("__IMPL(" + item + ")");
        }

        iteratorMacro.params = {{"__IMPL"}};
        iteratorMacro.name   = record.iteratorMacroName;
        decls.push_back(builder.Macro(iteratorMacro));
    }

    for (auto const& sub : record.types) {
        decls.push_back(convert(sub));
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
            decls.push_back(builder.Using(AB::UsingParams{
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
        decls.push_back(builder.Field(RDP::Field{
            .params = AB::ParmVarParams{
                .type   = AB::QualType(record.variantName),
                .name   = record.variantField,
                .defArg = record.variantValue,
            }}));
    }

    return decls;
}


AB::Res GenConverter::convert(const GD& desc) {
    Vec<AB::Res> decls;
    for (auto const& item : desc.entries) {
        decls.append(convert(item));
    }

    decls.append(std::move(pendingToplevel));
    return builder.TranslationUnit(decls);
}


Vec<ASTBuilder::Res> GenConverter::convert(const GenTu::Entry& entry) {
    Vec<AB::Res> decls;
    std::visit(
        overloaded{
            [&](GD::Include const& Include) {
                decls.push_back(
                    builder.Include(Include.what, Include.isSystem));
            },
            [&](SPtr<GD::Enum> const& Enum) {
                decls.push_back(convert(*Enum));
            },
            [&](SPtr<GD::Function> const& Func) {
                decls.push_back(convert(*Func));
            },
            [&](SPtr<GD::Struct> item) {
                decls.push_back(convert(*item));
            },
            [&](SPtr<GD::TypeGroup> item) {
                decls.append(convert(*item));
            },
            [&](GD::Pass const& Pass) {
                decls.push_back(builder.string(Pass.what));
            },
            [&](SPtr<GD::Namespace> space) {
                decls.push_back(convert(*space));
            },
            [](auto const& it) { qFatal("Unexpected kind"); },
        },
        entry);
    return decls;
}

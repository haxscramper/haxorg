#include "gen_converter.hpp"

AB::ParmVarDeclParams toParams(AB& builder, GD::Ident const& ident) {
    AB::ParmVarDeclParams result{};
    result.name = ident.name;
    return result;
}

AB::FunctionDeclParams convert(AB& builder, const GD::Function& func) {
    AB::FunctionDeclParams decl;
    decl.ResultTy = builder.Type(func.result);
    decl.Name     = func.name;
    decl.doc      = convert(builder, func.doc);

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
        .bases = record.bases,
        .doc   = convert(builder, record.doc),
    };

    for (auto const& member : record.fields) {
        params.members.push_back(RDP::Member{RDP::Field{
            .params = AB::ParmVarDeclParams{
                .name = member.name,
                .type = builder.Type(member.type),
            }}});
    }

    for (auto const& method : record.methods) {
        params.members.push_back(RDP::Member{AB::RecordDeclParams::Method{
            .params    = convert(builder, method),
            .isConst   = method.isConst,
            .isVirtual = method.isVirtual,
            .isStatic  = method.isStatic,
        }});
    }

    return params;
}

Vec<AB::Res> convert(AB& builder, const GD::TypeGroup& record) {
    Vec<AB::Res> decls;

    for (auto const& sub : record.types) {
        decls.push_back(builder.RecordDecl(convert(builder, sub)));
    }

    return decls;
}


AB::Res convert(AB& builder, const GD& desc) {
    Vec<AB::Res> decls;
    Vec<Str>     typeNames;
    for (auto const& item : desc.entries) {
        if (std::holds_alternative<GD::Struct>(item)) {
            typeNames.push_back(std::get<GD::Struct>(item).name);
        }
    }

    AB::EnumDeclParams enumDecl;
    for (auto const& item : typeNames) {
        enumDecl.fields.push_back(AB::EnumDeclParams::Field{.name = item});
    }

    enumDecl.name = desc.enumName;
    decls.push_back(builder.EnumDecl(enumDecl));

    AB::MacroDeclParams iteratorMacro;

    for (auto const& item : typeNames) {
        iteratorMacro.definition.push_back("__IMPL(" + item + ")");
    }

    iteratorMacro.params = {{"__IMPL"}};
    iteratorMacro.name   = desc.iteratorMacroName;
    decls.push_back(builder.MacroDecl(iteratorMacro));


    for (auto const& item : desc.entries) {
        if (std::holds_alternative<GD::Struct>(item)) {
            decls.push_back(builder.RecordDecl(
                convert(builder, std::get<GD::Struct>(item))));
        } else if (std::holds_alternative<GD::TypeGroup>(item)) {
            decls.append(convert(builder, std::get<GD::TypeGroup>(item)));
        } else {
            qFatal("Unexpected kind");
        }
    }

    return builder.TranslationUnit(decls);
}

AB::DocParams convert(AB& builder, const GenDescription::Doc& doc) {
    return AB::DocParams{.brief = doc.brief, .full = doc.full};
}

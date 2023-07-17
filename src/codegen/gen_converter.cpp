#include "gen_converter.hpp"

AB::ParmVarDeclParams toParams(
    ASTBuilder&      builder,
    GD::Ident const& ident) {
    AB::ParmVarDeclParams result{};
    result.name = ident.name;
    return result;
}

AB::FunctionDeclParams convert(
    ASTBuilder&         builder,
    const GD::Function& func) {
    AB::FunctionDeclParams decl;
    decl.ResultTy = builder.Type(func.result);
    decl.Name     = func.name;
    decl.doc      = convert(builder, func.doc);

    for (auto const& parm : func.arguments) {
        decl.Args.push_back(toParams(builder, parm));
    }

    return decl;
}

ASTBuilder::Res convert(ASTBuilder& builder, const GD::Ident& ident) {
    return builder.ParmVarDecl(toParams(builder, ident));
}

ASTBuilder::RecordDeclParams convert(
    ASTBuilder&       builder,
    const GD::Struct& record) {
    using RDP = ASTBuilder::RecordDeclParams;
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

Vec<ASTBuilder::Res> convert(
    ASTBuilder&          builder,
    const GD::TypeGroup& record) {
    Vec<ASTBuilder::Res> decls;

    for (auto const& sub : record.types) {
        decls.push_back(builder.RecordDecl(convert(builder, sub)));
    }

    return decls;
}


ASTBuilder::Res convert(ASTBuilder& builder, const GD& desc) {
    Vec<ASTBuilder::Res> decls;
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

ASTBuilder::DocParams convert(
    ASTBuilder&                builder,
    const GenDescription::Doc& doc) {
    return ASTBuilder::DocParams{.brief = doc.brief, .full = doc.full};
}

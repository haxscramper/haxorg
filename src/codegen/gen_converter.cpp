#include "gen_converter.hpp"

AB::ParmVarDeclParams toParams(
    ASTBuilder&      builder,
    GD::Ident const& ident) {
    AB::ParmVarDeclParams result{};
    result.name = ident.name;
    return result;
}

ASTBuilder::Res convert(ASTBuilder& builder, const GD::Function& func) {
    AB::FunctionDeclParams decl;

    for (auto const& parm : func.arguments) {
        decl.Args.push_back(toParams(builder, parm));
    }

    return builder.FunctionDecl(decl);
}

ASTBuilder::Res convert(ASTBuilder& builder, const GD::Ident& ident) {
    return builder.ParmVarDecl(toParams(builder, ident));
}

ASTBuilder::Res convert(ASTBuilder& builder, const GD::Struct& record) {
    using RDP = ASTBuilder::RecordDeclParams;
    RDP params{.name = record.name};
    for (auto const& member : record.fields) {
        AB::ParmVarDeclParams parmDecl;
        parmDecl.name = member.name;
        parmDecl.type = builder.Type(member.type);
        params.members.push_back(
            RDP::Member{RDP::Field{.params = parmDecl}});
    }

    auto decl = builder.RecordDecl(params);
    return decl;
}

Vec<ASTBuilder::Res> convert(
    ASTBuilder&          builder,
    const GD::TypeGroup& record) {
    Vec<ASTBuilder::Res> decls;

    for (auto const& sub : record.types) {
        decls.push_back(convert(builder, sub));
    }

    return decls;
}


ASTBuilder::Res convert(ASTBuilder& builder, const GD& desc) {
    Vec<ASTBuilder::Res> decls;
    for (auto const& item : desc.entries) {
        if (std::holds_alternative<GD::Struct>(item)) {
            decls.push_back(convert(builder, std::get<GD::Struct>(item)));
        } else if (std::holds_alternative<GD::TypeGroup>(item)) {
            decls.append(convert(builder, std::get<GD::TypeGroup>(item)));
        } else {
            qFatal("Unexpected kind");
        }
    }

    return builder.TranslationUnit(decls);
}

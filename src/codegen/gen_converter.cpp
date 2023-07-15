#include "gen_converter.hpp"

AB::ParmVarDeclParams toParams(
    ASTBuilder&      builder,
    GD::Ident const& ident) {
    AB::ParmVarDeclParams result{};
    result.name = ident.name;
    return result;
}

FunctionDecl* convert(ASTBuilder& builder, const GD::Function& func) {
    AB::FunctionDeclParams     decl;
    Vec<AB::ParmVarDeclParams> params;

    for (auto const& parm : func.arguments) {
        params.push_back(toParams(builder, parm));
    }

    return builder.FunctionDecl(decl, params);
}

ParmVarDecl* convert(ASTBuilder& builder, const GD::Ident& ident) {
    return builder.ParmVarDecl(toParams(builder, ident));
}

CXXRecordDecl* convert(ASTBuilder& builder, const GD::Struct& record) {
    return builder.CXXRecordDecl({.name = record.name});
}

Vec<clang::Decl*> convert(
    ASTBuilder&          builder,
    const GD::TypeGroup& record) {
    Vec<clang::Decl*> decls;

    for (auto const& sub : record.types) {
        decls.push_back(convert(builder, sub));
    }

    return decls;
}


TranslationUnitDecl* convert(ASTBuilder& builder, const GD& desc) {
    Vec<clang::Decl*> decls;
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

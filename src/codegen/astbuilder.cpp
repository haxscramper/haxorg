#include "astbuilder.hpp"

clang::ParmVarDecl* ASTBuilder::ParmVarDecl(const ParmVarDeclParams& p) {
    return ParmVarDecl::Create(
        ctx(),
        dc(),
        sl(),
        sl(),
        id(p.name),
        p.type,
        nullptr,
        p.storage,
        p.defArg);
}

clang::FunctionDecl* ASTBuilder::FunctionDecl(
    FunctionDeclParams            p,
    const Vec<ParmVarDeclParams>& params) {
    if (p.ResultTy.isNull()) {
        p.ResultTy = context->VoidTy;
    }
    Vec<class ParmVarDecl*> passParams;
    if (!params.empty()) {
        p.ArgsTy.clear();
        for (const auto& param : params) {
            passParams.push_back(ParmVarDecl(param));
            assert(!param.type.isNull());
            p.ArgsTy.push_back(param.type);
        }
    }

    auto res = FunctionDecl::Create(
        ctx(),                    // C
        dc(),                     // DC
        sl(),                     // StartLoc
        sl(),                     // NLoc
        name(p.Name),             // N
        context->getFunctionType( // T
            p.ResultTy,
            p.ArgsTy,
            FunctionProtoType::ExtProtoInfo()),
        nullptr,   // TInfo
        p.Storage, // SC
        true,      // UsesFPIntrin
        p.Inline   // isInlineSpecified
    );

    res->setParams(passParams);
    if (p.Body != nullptr) {
        res->setBody(p.Body);
    }
    return res;
}

clang::CXXRecordDecl* ASTBuilder::CXXRecordDecl(
    const TypeDeclParams& params) {
    auto record = CXXRecordDecl::Create(
        ctx(), params.tagKind, dc(), sl(), sl(), id(params.name));
    return record;
}

clang::VarDecl* ASTBuilder::VarDecl(VarDeclParams p) {
    if (p.Type.isNull()) {
        p.Type = context->getAutoDeductType();
    }

    auto result = clang::VarDecl::Create(
        ctx(), dc(), sl(), sl(), id(p.Name), p.Type, nullptr, p.Storage);

    if (p.Init != nullptr) {
        result->setInit(p.Init);
    }
    return result;
}

clang::IfStmt* ASTBuilder::IfStmt(const IfStmtParams& p) {
    return IfStmt::Create(
        ctx(),
        sl(),
        p.kind,
        p.Init,
        p.Var,
        p.Cond,
        sl(),
        sl(),
        CompoundStmt({p.Then}),
        sl(),
        p.Else.empty() ? nullptr : CompoundStmt({p.Else}));
}

clang::IfStmt* ASTBuilder::IfStmt(const ArrayRef<IfStmtParams>& p) {
    if (p.size() == 1) {
        return IfStmt(p[0]);
    } else {
        auto p0 = p[0];
        p0.Else = {IfStmt(p.slice(1))};
        return IfStmt(p0);
    }
}

clang::BinaryOperator* ASTBuilder::BinaryOperator(
    const BinaryOperatorParams& p) {
    return BinaryOperator::Create(
        ctx(),
        p.lhs,
        p.rhs,
        p.opc,
        QualType(),
        p.VK,
        p.OK,
        sl(),
        p.FPFeatures);
}

clang::UnaryOperator* ASTBuilder::UnaryOperator(
    const UnaryOperatorParams& p) {
    return clang::UnaryOperator::Create(
        ctx(),
        p.Expr,
        p.opc,
        ctx().VoidTy,
        p.VK,
        p.OK,
        sl(),
        false,
        p.FPFeatures);
}

clang::DeclRefExpr* ASTBuilder::Ref(clang::VarDecl* decl) {
    return DeclRefExpr::Create(
        ctx(),
        NestedNameSpecifierLoc(),
        sl(),
        decl,
        false,
        sl(),
        decl->getType(),
        ExprValueKind::VK_LValue);
}

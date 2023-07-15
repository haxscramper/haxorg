#pragma once

#include "gen_description.hpp"
#include "astbuilder.hpp"

using namespace clang;
using namespace llvm;

using AB = ASTBuilder;
using GD = GenDescription;


clang::ParmVarDecl*  convert(ASTBuilder& builder, GD::Ident const& ident);
clang::FunctionDecl* convert(
    ASTBuilder&         builder,
    GD::Function const& func);
clang::CXXRecordDecl* convert(
    ASTBuilder&       builder,
    GD::Struct const& record);
clang::TranslationUnitDecl* convert(ASTBuilder& builder, GD const& desc);

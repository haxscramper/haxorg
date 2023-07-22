#pragma once

#include "gen_description.hpp"
#include "astbuilder.hpp"

using AB = ASTBuilder;
using GD = GenDescription;


ASTBuilder::Res convert(ASTBuilder& builder, GD::Ident const& ident);
AB::FunctionDeclParams convert(
    ASTBuilder&         builder,
    GD::Function const& func);
ASTBuilder::RecordDeclParams convert(
    ASTBuilder&       builder,
    GD::Struct const& record);
ASTBuilder::EnumDeclParams convert(
    ASTBuilder&     builder,
    GD::Enum const& entry);
Vec<ASTBuilder::Res> convert(
    ASTBuilder&          builder,
    GD::TypeGroup const& entry);
Vec<ASTBuilder::Res>  convert(ASTBuilder& builder, GD::Entry const& entry);
ASTBuilder::Res       convert(ASTBuilder& builder, GD const& desc);
ASTBuilder::DocParams convert(ASTBuilder& builder, GD::Doc const& doc);

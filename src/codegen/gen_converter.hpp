#pragma once

#include "gen_description.hpp"
#include "astbuilder.hpp"

using AB = ASTBuilder;
using GD = GenTu;


ASTBuilder::Res convert(ASTBuilder& builder, GD::Ident const& ident);
AB::FunctionDeclParams convert(
    ASTBuilder&         builder,
    GD::Function const& func);
ASTBuilder::RecordDeclParams convert(
    ASTBuilder&       builder,
    GD::Struct const& record);
Pair<ASTBuilder::EnumDeclParams, AB::Res> convert(
    ASTBuilder&     builder,
    GD::Enum const& entry,
    bool            nested);
Vec<ASTBuilder::Res> convert(
    ASTBuilder&          builder,
    GD::TypeGroup const& entry);
Vec<ASTBuilder::Res>  convert(ASTBuilder& builder, GD::Entry const& entry);
ASTBuilder::Res       convert(ASTBuilder& builder, GD const& desc);
ASTBuilder::DocParams convert(ASTBuilder& builder, GD::Doc const& doc);
ASTBuilder::TemplateParamParams::Spec convert(
    ASTBuilder&      builder,
    CVec<GD::TParam> Params);

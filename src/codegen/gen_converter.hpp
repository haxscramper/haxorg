#pragma once

#include "gen_description.hpp"
#include "astbuilder.hpp"

using AB = ASTBuilder;
using GD = GenTu;

struct GenConverter {
    using Res = AB::Res;
    Vec<Res> pendingToplevel;
    bool     isSource = false;

    Res convert(ASTBuilder& builder, GD::Ident const& ident);
    AB::FunctionDeclParams convert(
        ASTBuilder&         builder,
        GD::Function const& func);
    ASTBuilder::RecordDeclParams convert(
        ASTBuilder&       builder,
        GD::Struct const& record);
    ASTBuilder::EnumDeclParams convert(
        ASTBuilder&     builder,
        GD::Enum const& entry,
        bool            nested);
    Vec<Res> convert(ASTBuilder& builder, GD::TypeGroup const& entry);
    Vec<Res> convert(ASTBuilder& builder, GD::Entry const& entry);
    Res      convert(ASTBuilder& builder, GD const& desc);
    Pair<Res, Res> convert(ASTBuilder& builder, GenUnit const& unit);
    ASTBuilder::DocParams convert(ASTBuilder& builder, GD::Doc const& doc);
    ASTBuilder::TemplateParamParams::Spec convert(
        ASTBuilder&      builder,
        CVec<GD::TParam> Params);
};

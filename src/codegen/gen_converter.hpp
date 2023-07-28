#pragma once

#include "gen_description.hpp"
#include "astbuilder.hpp"

using AB = ASTBuilder;
using GD = GenTu;

struct GenConverter {
    using Res = AB::Res;
    GenConverter(ASTBuilder& builder, bool isSource)
        : builder(builder), isSource(isSource) {}

    ASTBuilder& builder;
    Vec<Res>    pendingToplevel;
    bool        isSource = false;

    ASTBuilder::TemplateParamParams::Spec convert(CVec<GD::TParam> Params);

    Res                          convert(GD const& desc);
    Res                          convert(GD::Ident const& ident);
    AB::FunctionDeclParams       convert(GD::Function const& func);
    ASTBuilder::RecordDeclParams convert(GD::Struct const& record);
    ASTBuilder::EnumDeclParams convert(GD::Enum const& entry, bool nested);
    Vec<Res>                   convert(GD::TypeGroup const& entry);
    Vec<Res>                   convert(GD::Entry const& entry);
    ASTBuilder::DocParams      convert(GD::Doc const& doc);
};

#pragma once

#include "gen_description.hpp"
#include "astbuilder.hpp"

using AB = ASTBuilder;
using GD = GenTu;

struct GenConverter {
    using Res = AB::Res;
    GenConverter(ASTBuilder& builder, bool isSource)
        : builder(builder), isSource(isSource) {}

    ASTBuilder&               builder;
    Vec<Res>                  pendingToplevel;
    bool                      isSource = false;
    Vec<ASTBuilder::QualType> context;

    struct WithContext {
        GenConverter* conv;
        ~WithContext() { conv->context.pop_back(); }
        WithContext(GenConverter* conv, ASTBuilder::QualType typ)
            : conv(conv) {
            conv->context.push_back(typ);
        }
    };

    ASTBuilder::TemplateParams::Group convertParams(
        CVec<GD::TParam> Params);
    AB::FunctionParams convertFunction(GD::Function const& func);
    ASTBuilder::DocParams  convertDoc(GD::Doc const& doc);
    AB::ParmVarParams  convertIdent(GD::Ident const& ident);

    Res      convert(GD::Function const& func);
    Res      convert(GD const& desc);
    Res      convert(GD::Ident const& ident);
    Res      convert(GD::Struct const& record);
    Res      convert(GD::Enum const& entry);
    Vec<Res> convert(GD::TypeGroup const& entry);
    Vec<Res> convert(GD::Entry const& entry);
};

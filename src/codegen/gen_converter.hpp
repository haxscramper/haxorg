#pragma once

#include "gen_description.hpp"
#include "astbuilder.hpp"

using AB = ASTBuilder;
using GD = GenDescription;


ASTBuilder::Res convert(ASTBuilder& builder, GD::Ident const& ident);
ASTBuilder::Res convert(ASTBuilder& builder, GD::Function const& func);
ASTBuilder::Res convert(ASTBuilder& builder, GD::Struct const& record);
ASTBuilder::Res convert(ASTBuilder& builder, GD const& desc);

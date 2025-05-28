#pragma once
#include <haxorg/sem/ImmOrg.hpp>

namespace org::imm {
std::string serializeToText(std::shared_ptr<ImmAstContext> const& store);
void        serializeFromText(
           std::string const&              binary,
           std::shared_ptr<ImmAstContext>& store);
} // namespace org::imm

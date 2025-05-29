#pragma once
#include <haxorg/sem/ImmOrg.hpp>

namespace org::imm {
std::string serializeToText(std::shared_ptr<ImmAstContext> const& store);
void        serializeFromText(
           std::string const&              binary,
           std::shared_ptr<ImmAstContext>& store);
json        serializeFromTextToJson(std::string const& binary);
std::string serializeFromTextToTreeDump(std::string const& binary);
} // namespace org::imm

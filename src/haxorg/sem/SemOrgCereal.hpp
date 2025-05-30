#pragma once
#include <haxorg/sem/ImmOrg.hpp>

namespace org::imm {
[[refl]] std::string serializeToText(
    std::shared_ptr<ImmAstContext> const& store);
[[refl]] void serializeFromText(
    std::string const&              binary,
    std::shared_ptr<ImmAstContext>& store);
json                 serializeFromTextToJson(std::string const& binary);
[[refl]] std::string serializeFromTextToTreeDump(
    std::string const& binary);
} // namespace org::imm

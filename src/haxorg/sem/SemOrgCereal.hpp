#pragma once
#include <haxorg/sem/ImmOrg.hpp>

namespace org::imm {
std::string serializeToPortableBinary(
    std::shared_ptr<ImmAstContext> const& store);
std::string serializeToJSON(std::shared_ptr<ImmAstContext> const& store);
void        readFromPortableBinary(
           std::string const&              binary,
           std::shared_ptr<ImmAstContext>& store);
} // namespace org::imm

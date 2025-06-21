#pragma once
#include <haxorg/sem/ImmOrg.hpp>
#include <haxorg/sem/ImmOrgGraph.hpp>

namespace org::imm {
[[refl(R"({"unique-name": "serializeAstContextToText"})")]] std::string serializeToText(
    std::shared_ptr<ImmAstContext> const& store);
[[refl(R"({"unique-name": "serializeAstContextFromText"})")]] void serializeFromText(
    std::string const&                    binary,
    std::shared_ptr<ImmAstContext> const& store);

[[refl(R"({"unique-name": "serializAstEpochToText"})")]] std::string serializeToText(
    std::shared_ptr<ImmAstReplaceEpoch> const& store);
[[refl(R"({"unique-name": "serializAstEpochFromText"})")]] void serializeFromText(
    std::string const&                         binary,
    std::shared_ptr<ImmAstReplaceEpoch> const& store);

[[refl(R"({"unique-name": "serializeMapGraphToText"})")]] std::string serializeToText(
    std::shared_ptr<org::graph::MapGraph> const& store);
[[refl(R"({"unique-name": "serializeMapGraphFromText"})")]] void serializeFromText(
    std::string const&                           binary,
    std::shared_ptr<org::graph::MapGraph> const& store);


json                 serializeFromTextToJson(std::string const& binary);
[[refl]] std::string serializeFromTextToTreeDump(
    std::string const& binary);
} // namespace org::imm

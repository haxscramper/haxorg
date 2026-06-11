#pragma once

#include <haxorg/imm/ImmOrg.hpp>
#include <haxorg/imm/ImmOrgAdapter.hpp>
#include <hstd/stdlib/Outcome.hpp>
#include <hstd/stdlib/JsonSerde.hpp>

namespace org::imm {
bool isDescriptionItem(org::imm::ImmAdapter const& node);
bool isLinkedDescriptionItemNode(org::imm::ImmAdapter const& n);

bool isLinkedDescriptionItem(org::imm::ImmAdapter const& n);
/// \brief Check if getBoxedNode is a description list. By design, having
/// at least one description list item in the description list makes the
/// whole list into a linked description as well.
bool isLinkedDescriptionList(org::imm::ImmAdapter const& n);

/// \brief Check if a node is placed in the description list item or *is* a
/// description list item.
bool isInSubtreeDescriptionList(org::imm::ImmAdapter const& n);

bool isAttachedDescriptionList(org::imm::ImmAdapter const& n);

template <typename T>
hstd::outcome::result<T, std::string> getStructuredProperty(
    org::imm::ImmAdapter const& node,
    std::string const&          kind) {

    hstd::Opt<sem::NamedProperty> opt_prop;

    if (auto subtree = node.asOpt<org::imm::ImmSubtree>()) {
        opt_prop = subtree->getPropertyByKind("customjson", kind);
    } else if (auto doc = node.asOpt<org::imm::ImmDocument>()) {
        opt_prop = node.ctx.lock()
                       ->adaptUnrooted(doc.value()->options)
                       .as<org::imm::ImmDocumentOptions>()
                       .getPropertyByKind("customjson", kind);
    } else {
        return hstd::fmt("Node {} does not contain subtree", node);
    }

    BOOST_OUTCOME_TRY_OPTIONAL(
        property,
        opt_prop,
        hstd::fmt("Property :prop_json:{}: not found", kind));

    BOOST_OUTCOME_TRY_SUB_VARIANT(json_data, property, CustomSubtreeJson);
    try {
        return hstd::from_json_eval<T>(json_data.value.getRef());
    } catch (json::type_error& err) {
        return hstd::fmt(
            "Property :prop_json:{}: JSON did not match the expected "
            "structure. While reading type {}, got error: {}. JSON syntax "
            "is valid, the value is {}",
            kind,
            hstd::value_metadata<T>::typeName(),
            err.what(),
            json_data.value.getRef().dump());
    }
}

} // namespace org::imm
